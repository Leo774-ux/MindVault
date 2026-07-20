#include "platform.h"
#include <stdio.h>
#include <stdlib.h>

// Linux 专属的具体实现
void platform_init(void) {
    // 可以在这里加一些 Linux 启动时的初始化代码
}

void platform_cleanup(void) {
    // Linux 退出时的清理代码
}

const char* platform_get_data_dir(void) {
    static char dir[256];
    const char* home = getenv("HOME");
    if (home) { 
        snprintf(dir, sizeof(dir), "%s/.mindvault", home); 
        return dir; 
    }
    return "/tmp/mindvault";
}
