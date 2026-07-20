#ifndef PLATFORM_H
#define PLATFORM_H
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
    #define PLATFORM_MACOS
#else
    #define PLATFORM_LINUX
#endif
#ifdef PLATFORM_WINDOWS
    #define PATH_SEP '\\'
#else
    #define PATH_SEP '/'
#endif
void platform_init(void);
void platform_cleanup(void);
const char* platform_get_data_dir(void);
#endif
