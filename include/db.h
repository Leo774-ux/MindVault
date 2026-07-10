#ifndef MINDVAULT_DB_H
#define MINDVAULT_DB_H

#include <stddef.h>

// 打开/关闭数据库（数据文件 + 索引文件）
void db_open(const char *data_path, const char *idx_path);
void db_close(void);

// 插入数据，返回 slot id，失败返回 -1
int db_insert(const char *data);

// 查询数据（走索引），返回指针，NULL 表示未找到
const char* db_query(int id);

// 按值查找（走索引），返回第一个匹配的 slot id，-1 表示未找到
int db_find_by_key(int key);

// 删除数据
int db_delete(int id);

#endif
