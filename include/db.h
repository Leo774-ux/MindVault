#ifndef MINDVAULT_DB_H
#define MINDVAULT_DB_H

#include <stddef.h>

// 打开/关闭数据库
void db_open(const char *path);
void db_close(void);

// 插入数据，返回 slot id，失败返回 -1
int db_insert(const char *data);

// 查询数据，返回指针，NULL 表示未找到
const char* db_query(int id);

// 删除数据（标记 unused）
int db_delete(int id);

#endif
