#include "platform.h"
#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
void platform_init(void) {}
void platform_cleanup(void) {}
const char* platform_get_data_dir(void) {
    static char dir[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, dir))) {
        strcat(dir, "\\MindVault"); return dir;
    }
    return "C:\\MindVault";
}
