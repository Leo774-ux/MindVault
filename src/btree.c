#include <stddef.h>
// Placeholder B-tree implementation
#include <stddef.h>   // ✅ 修复 NULL 未声明
#include "btree.h"
void btree_init(void) {}
void btree_insert(int key, void *value) {}
void* btree_search(int key) { return NULL; }
void btree_delete(int key) {}
