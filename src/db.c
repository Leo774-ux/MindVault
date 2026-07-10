#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "../include/db.h"
#include "../include/auth.h"

#define SLOT_SIZE 256
#define MAX_SLOTS 1024
#define AUTH_GUEST 0
#define AUTH_USER  1
#define AUTH_ADMIN 2

typedef struct {
    int   used;
    char  data[SLOT_SIZE - 4];
} Slot;

static int    fd;
static Slot  *slots;
static int    slot_count;

void db_open(const char *path) {
    fd = open(path, O_RDWR | O_CREAT, 0644);
    if (fd < 0) { perror("open"); exit(1); }

    size_t size = MAX_SLOTS * sizeof(Slot);
    ftruncate(fd, size);

    slots = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (slots == MAP_FAILED) { perror("mmap"); exit(1); }

    slot_count = MAX_SLOTS;
}

void db_close(void) {
    size_t size = MAX_SLOTS * sizeof(Slot);
    munmap(slots, size);
    close(fd);
}

int db_insert(const char *data) {
    if (auth_check(AUTH_USER, "insert") != 0) return -1;

    int i;
    for (i = 0; i < slot_count; i++) {
        if (!slots[i].used) {
            slots[i].used = 1;
            strncpy(slots[i].data, data, sizeof(slots[i].data) - 1);
            slots[i].data[sizeof(slots[i].data) - 1] = '\0';
            return i;
        }
    }
    return -1;
}
const char* db_query(int id) {
    if (id < 0 || id >= slot_count || !slots[id].used) return NULL;
    return slots[id].data;
}

int db_delete(int id) {
    if (id < 0 || id >= slot_count || !slots[id].used) return -1;
    slots[id].used = 0;
    memset(slots[id].data, 0, sizeof(slots[id].data));
    return 0;
}

int main(void) {
    auth_set_level(AUTH_GUEST);
    db_open("test.mv");

    // 尝试插入（GUEST 权限不足）
    int id = db_insert("should fail");
    if (id == -1) printf("Insert blocked as expected.\n");

    // 提升权限
    auth_set_level(AUTH_USER);
    id = db_insert("hello mindvault");
    printf("inserted id=%d\n", id);

    // 尝试删除（USER 权限不足）
    auth_set_level(AUTH_USER);
    if (db_delete(id) == -1) printf("Delete blocked as expected.\n");

    // ADMIN 权限可以删除
    auth_set_level(AUTH_ADMIN);
    if (db_delete(id) == 0) printf("Deleted successfully.\n");

    db_close();
    return 0;
}
