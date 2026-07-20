#include "platform.h"
#include <stdio.h>
#include <stdlib.h>

// Mac 专属的具体实现
void platform_init(void) {}

void platform_cleanup(void) {}

const char* platform_get_data_dir(void) {
    static char dir[256];
    const char* home = getenv("HOME");
    if (home) { 
        snprintf(dir, sizeof(dir), "%s/Library/Application Support/MindVault", home); 
        return dir; 
    }
    return "/tmp/mindvault";
}
