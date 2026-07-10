#ifndef AUTH_H
#define AUTH_H

// 权限等级
typedef enum {
    AUTH_GUEST = 0,   // 只读
    AUTH_USER  = 1,   // 读写（增删改）
    AUTH_ADMIN = 2    // 全部权限（包括管理操作）
} AuthLevel;

// 设置当前会话权限
void auth_set_level(AuthLevel level);

// 获取当前权限
AuthLevel auth_get_level(void);

// 检查权限：需要的最低等级，返回0表示允许，-1表示拒绝并警告
int auth_check(AuthLevel required, const char *operation);

#endif
