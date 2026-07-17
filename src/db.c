#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"

Database db = {0};

void db_init(void) {
    db.is_open = 0;
    db.permission_level = 0;
    memset(db.records, 0, sizeof(db.records));
}

int db_open(const char *path) {
    strncpy(db.path, path, sizeof(db.path)-1);
    db.is_open = 1;
    printf("Opening database: %s\n", db.path);
    return 0;
}

void db_close(void) {
    if (!db.is_open) return;
    printf("Closing database: %s\n", db.path);
    db.is_open = 0;
}

int db_insert(int id, const char *data) {
    if (!db.is_open) return -1;
    for (int i = 0; i < 100; i++) {
        if (db.records[i].id == 0) {
            db.records[i].id = id;
            strncpy(db.records[i].data, data, sizeof(db.records[i].data)-1);
            return 0;
        }
    }
    return -1;
}

Record* db_query(int id) {
    if (!db.is_open) return NULL;
    for (int i = 0; i < 100; i++) {
        if (db.records[i].id == id) {
            return &db.records[i];
        }
    }
    return NULL;
}

int db_delete(int id) {
    if (!db.is_open) return -1;
    for (int i = 0; i < 100; i++) {
        if (db.records[i].id == id) {
            db.records[i].id = 0;
            memset(db.records[i].data, 0, sizeof(db.records[i].data));
            return 0;
        }
    }
    return -1;
}

void db_status(void) {
    if (!db.is_open) {
        printf("Database is not open.\n");
        return;
    }
    printf("=== Database Status ===\n");
    printf("Path: %s\n", db.path);
    printf("Is Open: %s\n", db.is_open ? "Yes" : "No");
    printf("Permission Level: %d\n", db.permission_level);
    int count = 0;
    for (int i = 0; i < 100; i++) {
        if (db.records[i].id != 0) count++;
    }
    printf("Total Records: %d\n", count);
}
