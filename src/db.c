#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "../include/db.h"
#include "../include/auth.h"
#include "../include/btree.h"

#define SLOT_SIZE 256
#define MAX_SLOTS 1024

typedef struct {
    int   used;
    char  data[SLOT_SIZE - 4];
} Slot;

static int    fd;
static Slot  *slots;
static int    slot_count;

void db_open(const char *data_path, const char *idx_path) {
    // 打开数据文件
    fd = open(data_path, O_RDWR | O_CREAT, 0644);
    if (fd < 0) { perror("open data"); exit(1); }

    size_t size = MAX_SLOTS * sizeof(Slot);
    ftruncate(fd, size);

    slots = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (slots == MAP_FAILED) { perror("mmap data"); exit(1); }

    slot_count = MAX_SLOTS;

    // 打开索引文件
    btree_init(idx_path);
}

void db_close(void) {
    size_t size = MAX_SLOTS * sizeof(Slot);
    munmap(slots, size);
    close(fd);
    btree_close();
}

int db_insert(const char *data) {
    if (auth_check(AUTH_USER, "insert") != 0) return -1;

    int i;
    for (i = 0; i < slot_count; i++) {
        if (!slots[i].used) {
            slots[i].used = 1;
            strncpy(slots[i].data, data, sizeof(slots[i].data) - 1);
            slots[i].data[sizeof(slots[i].data) - 1] = '\0';

            // 在 B+树中插入索引（以 slot id 为 key）
            btree_insert(i);

            return i;
        }
    }
    return -1;
}

const char* db_query(int id) {
    if (auth_check(AUTH_GUEST, "query") != 0) return NULL;

    // 先走索引查找
    int found = btree_search(id);
    if (found == -1) return NULL;

    // 索引命中，直接访问 slot
    if (id < 0 || id >= slot_count || !slots[id].used) return NULL;
    return slots[id].data;
}

int db_find_by_key(int key) {
    if (auth_check(AUTH_GUEST, "find") != 0) return -1;
    return btree_search(key);
}

int db_delete(int id) {
    if (auth_check(AUTH_ADMIN, "delete") != 0) return -1;

    if (id < 0 || id >= slot_count || !slots[id].used) return -1;
    slots[id].used = 0;
    memset(slots[id].data, 0, sizeof(slots[id].data));

    // 从 B+树中删除索引
    btree_delete(id);

    return 0;
}
// 测试主函数
int main(void) {
    auth_set_level(AUTH_ADMIN);
    db_open("test.mv", "test.idx");

    int id1 = db_insert("hello");
    int id2 = db_insert("world");
    int id3 = db_insert("btree");

    printf("Before delete:\n");
    printf("  Find 0: %d\n", db_find_by_key(0));
    printf("  Find 1: %d\n", db_find_by_key(1));
    printf("  Find 2: %d\n", db_find_by_key(2));

    printf("\nDeleting id1 (key=0)...\n");
    db_delete(id1);

    printf("After delete:\n");
    printf("  Find 0: %d\n", db_find_by_key(0));
    printf("  Find 1: %d\n", db_find_by_key(1));
    printf("  Find 2: %d\n", db_find_by_key(2));

    db_close();
    return 0;
}
