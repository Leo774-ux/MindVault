// include/db.h
#ifndef DB_H
#define DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "auth.h" // ✅ 新增：引入 auth.h 以使用 AUTH_GUEST 等宏

#define MAX_PATH_LEN 256
#define MAX_DATA_SIZE 1024

// --- 结构体定义移到头文件里 ---
typedef struct Record {
    int id;             // 唯一ID
    off_t offset;       // 在文件中的偏移量
    char data[MAX_DATA_SIZE];
} Record;

typedef struct Database {
    FILE *file;
    char path[MAX_PATH_LEN];
    int permission_level; // 0: Guest, 1: Admin
    Record index[100];    // 简易索引数组
    int record_count;
} Database;

// 全局数据库实例声明
extern Database db;

// 函数声明
void db_init(void);
int db_open(const char *path);
void db_close(void);
int db_insert(const char *data, const char *source_ip);
Record* db_query(int id);
int db_delete(int id);
void db_status(void);

#endif
