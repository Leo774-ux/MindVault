#ifndef PLATFORM_H
#define PLATFORM_H

/* 1. 引入标准库核心头文件，定义 NULL */
#include <stddef.h>

/* 2. 引入标准输入输出，定义 printf 等 */
#include <stdio.h>

/* 3. 引入标准库，定义 malloc, free, getenv 等 */
#include <stdlib.h>

/* 平台初始化与清理 */
void platform_init(void);
void platform_cleanup(void);

/* 获取数据存储目录 */
const char* platform_get_data_dir(void);

#endif
