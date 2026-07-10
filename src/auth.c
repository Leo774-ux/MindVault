#include <stdio.h>
#include <time.h>
#include "../include/auth.h"

static AuthLevel current_level = AUTH_GUEST; // 默认最低权限

void auth_set_level(AuthLevel level) {
    current_level = level;
}

AuthLevel auth_get_level(void) {
    return current_level;
}

int auth_check(AuthLevel required, const char *operation) {
    if (current_level < required) {
        // 获取当前时间
        time_t now = time(NULL);
        char *time_str = ctime(&now);
        // 去掉换行符
        time_str[24] = '\0';

        // 输出警告到 stderr（可改为日志文件）
        fprintf(stderr,
            "\n⚠️  SECURITY ALERT ⚠️\n"
            "  Time:      %s\n"
            "  Operation: %s\n"
            "  Required:  %s\n"
            "  Current:   %s\n"
            "  Action:    DENIED\n\n",
            time_str,
            operation,
            required == AUTH_GUEST ? "GUEST" :
            required == AUTH_USER ? "USER" : "ADMIN",
            current_level == AUTH_GUEST ? "GUEST" :
            current_level == AUTH_USER ? "USER" : "ADMIN"
        );
        return -1; // 拒绝
    }
    return 0; // 允许
}
