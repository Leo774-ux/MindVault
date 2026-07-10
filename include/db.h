#ifndef DB_H
#define DB_H

#include <stdint.h>
#include <stddef.h>

typedef struct Record {
    uint8_t  used;
    uint32_t length;
    int32_t  prev;
    int32_t  next;
    char     data[];
} Record;

typedef struct {
    int    fd;
    void  *base;
    size_t file_size;
    int    first_free;
} Database;

void db_open(Database *db, const char *filename);
void db_close(Database *db);
int db_insert(Database *db, const char *data, int length);
Record* db_query(Database *db, int offset);
int db_delete(Database *db, int offset);

#endif
