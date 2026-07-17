#ifndef DB_H
#define DB_H
#include <stdio.h>
typedef struct { int id; long offset; char data[256]; } Record;
typedef struct { char path[256]; int is_open; int permission_level; Record records[100]; } Database;
extern Database db;
int db_open(const char *path);
void db_close(void);
void db_init(void);
int db_insert(int id, const char *data);
Record* db_query(int id);
int db_delete(int id);
void db_status(void);
#endif
