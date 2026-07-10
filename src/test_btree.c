#include <stdio.h>
#include "../include/btree.h"

int main(void) {
    btree_init("btree.idx");

    btree_insert(10);
    btree_insert(5);
    btree_insert(20);
    btree_insert(3);
    btree_insert(7);

    printf("search 5: %d\n", btree_search(5));   // 应该输出 5
    printf("search 15: %d\n", btree_search(15)); // 应该输出 -1

    btree_close();
    return 0;
}
