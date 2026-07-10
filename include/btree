#ifndef BTREE_H
#define BTREE_H

#define ORDER 4  // 每个节点最多存 3 个 key

typedef struct {
    int  keys[ORDER];        // 路由 key（slot id）
    int  children[ORDER+1];  // 子节点偏移（在文件中的位置）
    int  count;              // 当前 key 数量
    int  is_leaf;            // 1=叶子，0=内部节点
    int  next;               // 叶子节点的下一个节点偏移（链表用）
} BTreeNode;

// B+树操作
void btree_init(const char *path);
int  btree_insert(int key);
int  btree_search(int key);
void btree_close(void);

#endif
