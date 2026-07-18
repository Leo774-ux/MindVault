#ifndef MINDVAULT_H
#define MINDVAULT_H
typedef struct { int id; char* data; } Record;
int mv_init();
int mv_open(const char*);
int mv_insert(int, const char*);
Record* mv_query(int);
int mv_delete(int);
void mv_close();
void mv_status();
#endif
