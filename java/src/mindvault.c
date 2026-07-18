#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mindvault.h"

static Record* records[100];
static int next_id = 1;

int mv_init() { 
    memset(records, 0, sizeof(records)); 
    next_id = 1;
    return 0; 
}

int mv_open(const char* path) { 
    printf("[C Lib] Opening database at: %s\n", path);
    return 0; 
}

int mv_insert(int id, const char* data) {
    if (id <= 0 || id >= 100) return -1;
    if (records[id] != NULL) return -1; // 已存在
    
    records[id] = (Record*)malloc(sizeof(Record));
    records[id]->id = id;
    records[id]->data = strdup(data);
    return 0;
}

Record* mv_query(int id) {
    if (id <= 0 || id >= 100) return NULL;
    return records[id];
}

int mv_delete(int id) {
    if (id <= 0 || id >= 100) return -1;
    if (records[id] == NULL) return -1;
    
    free(records[id]->data);
    free(records[id]);
    records[id] = NULL;
    return 0;
}

void mv_close() { 
    printf("[C Lib] Closing database.\n");
}

void mv_status() { 
    printf("[C Lib] Database status checked.\n");
}
