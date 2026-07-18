#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mindvault.h"

static Record* records[100];

int mv_init() { memset(records, 0, sizeof(records)); return 0; }
int mv_open(const char* path) { printf("[C] Open: %s\n", path); return 0; }
int mv_insert(int id, const char* data) {
    if (id <= 0 || id >= 100) return -1;
    records[id] = (Record*)malloc(sizeof(Record));
    records[id]->id = id;
    records[id]->data = strdup(data);
    return 0;
}
Record* mv_query(int id) { return (id > 0 && id < 100) ? records[id] : NULL; }
int mv_delete(int id) {
    if (records[id]) { free(records[id]->data); free(records[id]); records[id] = NULL; }
    return 0;
}
void mv_close() { printf("[C] Close\n"); }
void mv_status() { printf("[C] Status\n"); }
