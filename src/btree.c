#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "../include/btree.h"

#define MAX_NODES 1024

static int   fd;
static BTreeNode *nodes;  // mmap 节点数组
static int   node_count;
static int   root_offset; // 根节点在数组中的下标

void btree_init(const char *path) {
    fd = open(path, O_RDWR | O_CREAT, 0644);
    if (fd < 0) { perror("open"); exit(1); }

    size_t size = MAX_NODES * sizeof(BTreeNode);
    ftruncate(fd, size);

    nodes = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (nodes == MAP_FAILED) { perror("mmap"); exit(1); }

    node_count = 1;
    root_offset = 0;

    // 初始化根节点为叶子
    nodes[0].is_leaf = 1;
    nodes[0].count = 0;
    nodes[0].next = -1;
}

// 在叶子节点中插入 key
static void leaf_insert(BTreeNode *node, int key) {
    int i = node->count - 1;
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i+1] = node->keys[i];
        i--;
    }
    node->keys[i+1] = key;
    node->count++;
}

// 分裂叶子节点
static int split_leaf(BTreeNode *parent, int child_idx) {
    BTreeNode *child = &nodes[parent->children[child_idx]];
    BTreeNode *new_node = &nodes[node_count++];
    new_node->is_leaf = 1;
    new_node->count = 0;
    new_node->next = child->next;

    int mid = ORDER / 2;
    for (int i = mid; i < ORDER; i++) {
        new_node->keys[new_node->count++] = child->keys[i];
    }
    child->count = mid;

    // 把中间 key 提升到父节点
    for (int i = parent->count; i > child_idx; i--) {
        parent->keys[i] = parent->keys[i-1];
        parent->children[i+1] = parent->children[i];
    }
    parent->keys[child_idx] = child->keys[mid];
    parent->children[child_idx+1] = node_count - 1;
    parent->count++;

    child->next = node_count - 1;
    return 0;
}

int btree_insert(int key) {
    BTreeNode *root = &nodes[root_offset];

    // 根节点满了，需要分裂
    if (root->count == ORDER) {
        BTreeNode *new_root = &nodes[node_count++];
        new_root->is_leaf = 0;
        new_root->count = 0;
        new_root->children[0] = root_offset;

        split_leaf(new_root, 0);
        root_offset = node_count - 1;
    }

    // 从根向下找插入位置
    int idx = root_offset;
    while (!nodes[idx].is_leaf) {
        BTreeNode *node = &nodes[idx];
        int i = 0;
        while (i < node->count && key > node->keys[i]) i++;
        idx = node->children[i];
    }

    // 插入叶子
    leaf_insert(&nodes[idx], key);
    return 0;
}

int btree_search(int key) {
    int idx = root_offset;
    while (!nodes[idx].is_leaf) {
        BTreeNode *node = &nodes[idx];
        int i = 0;
        while (i < node->count && key >= node->keys[i]) i++;
        idx = node->children[i];
    }

    // 在叶子中查找
    BTreeNode *leaf = &nodes[idx];
    for (int i = 0; i < leaf->count; i++) {
        if (leaf->keys[i] == key) return key;
    }
    return -1;
}

void btree_close(void) {
    size_t size = MAX_NODES * sizeof(BTreeNode);
    munmap(nodes, size);
    close(fd);
}
