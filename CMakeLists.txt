cmake_minimum_required(VERSION 3.10)
project(mindvault)

if(WIN32)
    set(PLATFORM_SRC src/platform/platform_win.c)
elseif(APPLE)
    set(PLATFORM_SRC src/platform/platform_mac.c)
else()
    set(PLATFORM_SRC src/platform/platform_linux.c)
endif()

set(SOURCES
    src/cli.c
    src/mindvault.c
    ${PLATFORM_SRC}
)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(mindvault ${SOURCES})

if(NOT WIN32 AND NOT APPLE)
    target_link_libraries(mindvault microhttpd m)
endif()
