#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "db.h"

#define ORDER 4

typedef struct {
    int keys[ORDER];
    int children[ORDER+1];
    int count;
    int is_leaf;
    int next;
} BTreeNode;

static BTreeNode *nodes = NULL;
static int node_count = 0;
static int root_offset = 0;

void btree_init(Database *db) {
    nodes = (BTreeNode*)calloc(1024, sizeof(BTreeNode));
    node_count = 1;
    root_offset = 0;
    nodes[0].is_leaf = 1;
    nodes[0].count = 0;
    nodes[0].next = -1;
    printf("B+Tree initialized (simplified).\n");
}

static void leaf_insert(BTreeNode *node, int key) {
    int i = node->count - 1;
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i+1] = node->keys[i];
        i--;
    }
    node->keys[i+1] = key;
    node->count++;
}

int btree_insert(Database *db, int offset, int length) {
    BTreeNode *root = &nodes[root_offset];
    if (root->count < ORDER) {
        leaf_insert(root, offset);
        return 0;
    }
    fprintf(stderr, "B+Tree node full, insertion ignored.\n");
    return -1;
}

void btree_delete(int offset) {
    BTreeNode *root = &nodes[root_offset];
    for (int i = 0; i < root->count; i++) {
        if (root->keys[i] == offset) {
            for (int j = i; j < root->count-1; j++)
                root->keys[j] = root->keys[j+1];
            root->count--;
            return;
        }
    }
}
