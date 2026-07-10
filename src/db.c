#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "db.h"
#include "btree.h"
#include "auth.h"

#define ALIGN(size, align) (((size) + (align) - 1) & ~((align) - 1))

void db_open(Database *db, const char *filename) {
    if (auth_check(AUTH_ADMIN, "open") != 0) return;

    db->fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (db->fd < 0) { perror("open"); exit(1); }

    struct stat st;
    if (fstat(db->fd, &st) < 0) { perror("fstat"); exit(1); }

    db->file_size = st.st_size;
    if (db->file_size == 0) {
        db->file_size = 4096;
        if (ftruncate(db->fd, db->file_size) < 0) { perror("ftruncate"); exit(1); }
    }

    db->base = mmap(NULL, db->file_size, PROT_READ | PROT_WRITE, MAP_SHARED, db->fd, 0);
    if (db->base == MAP_FAILED) { perror("mmap"); exit(1); }

    db->first_free = -1;
    btree_init(db);
}

int extend_file(Database *db, size_t needed) {
    size_t new_size = db->file_size + needed;
    new_size = ALIGN(new_size, 4096);

    if (munmap(db->base, db->file_size) < 0) { perror("munmap"); return -1; }
    if (ftruncate(db->fd, new_size) < 0) { perror("ftruncate"); return -1; }

    db->base = mmap(NULL, new_size, PROT_READ | PROT_WRITE, MAP_SHARED, db->fd, 0);
    if (db->base == MAP_FAILED) { perror("mmap"); return -1; }

    int old_size = db->file_size;
    db->file_size = new_size;
    return old_size;
}

int db_insert(Database *db, const char *data, int length) {
    if (auth_check(AUTH_USER, "insert") != 0) return -1;

    size_t total_needed = sizeof(Record) + length;
    total_needed = ALIGN(total_needed, 8);

    int offset = -1;
    int current = db->first_free;
    int prev = -1;

    while (current != -1) {
        Record *rec = (Record*)((char*)db->base + current);
        if (rec->length >= (int)total_needed) {
            if (prev != -1) {
                Record *prev_rec = (Record*)((char*)db->base + prev);
                prev_rec->next = rec->next;
            } else {
                db->first_free = rec->next;
            }
            if (rec->next != -1) {
                Record *next_rec = (Record*)((char*)db->base + rec->next);
                next_rec->prev = prev;
            }
            offset = current;
            break;
        }
        prev = current;
        current = rec->next;
    }

    if (offset == -1) {
        offset = extend_file(db, total_needed);
        if (offset < 0) return -1;
    }

    Record *rec = (Record*)((char*)db->base + offset);
    rec->used = 1;
    rec->length = length;
    rec->prev = -1;
    rec->next = -1;
    memcpy(rec->data, data, length);

    btree_insert(db, offset, length);
    return offset;
}

Record* db_query(Database *db, int offset) {
    if (auth_check(AUTH_GUEST, "query") != 0) return NULL;
    if (offset < 0 || offset >= (int)db->file_size) return NULL;

    Record *rec = (Record*)((char*)db->base + offset);
    if ((char*)rec + sizeof(Record) + rec->length > (char*)db->base + db->file_size) return NULL;
    if (!rec->used) return NULL;
    return rec;
}

int db_delete(Database *db, int offset) {
    if (auth_check(AUTH_ADMIN, "delete") != 0) return -1;
    if (offset < 0 || offset >= (int)db->file_size) return -1;

    Record *rec = (Record*)((char*)db->base + offset);
    if (!rec->used) return -1;

    rec->used = 0;
    btree_delete(offset);

    rec->next = db->first_free;
    rec->prev = -1;
    if (db->first_free != -1) {
        Record *old_first = (Record*)((char*)db->base + db->first_free);
        old_first->prev = offset;
    }
    db->first_free = offset;
    return 0;
}

void db_close(Database *db) {
    if (auth_check(AUTH_ADMIN, "close") != 0) return;
    if (db->base) munmap(db->base, db->file_size);
    if (db->fd >= 0) close(db->fd);
    db->base = NULL;
    db->fd = -1;
    db->file_size = 0;
    db->first_free = -1;
}

int main(void) {
    auth_set_level(AUTH_ADMIN);
    Database db;
    db_open(&db, "test.mv");

    int off1 = db_insert(&db, "hello", 5);
    int off2 = db_insert(&db, "this is a longer record!", 23);
    int off3 = db_insert(&db, "short", 5);

    printf("Inserted offsets: %d %d %d\n", off1, off2, off3);

    Record *r = db_query(&db, off1);
    if (r) printf("Query off1: %.*s\n", r->length, r->data);

    r = db_query(&db, off2);
    if (r) printf("Query off2: %.*s\n", r->length, r->data);

    printf("Deleting off1...\n");
    db_delete(&db, off1);
    printf("Query off1 after delete: %s\n", db_query(&db, off1) ? "exists" : "NULL");

    db_close(&db);
    printf("Done.\n");
    return 0;
}
