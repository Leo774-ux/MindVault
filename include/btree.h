#ifndef BTREE_H
#define BTREE_H
void btree_init(void);
void btree_insert(int key, void *value);
void* btree_search(int key);
void btree_delete(int key);
#endif
