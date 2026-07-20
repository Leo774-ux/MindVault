#ifndef MINDVAULT_H
#define MINDVAULT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char *data;
} Record;

typedef struct {
    void *db_handle;
} mindvault_app_t;

typedef struct {
    const char *path;
    void (*handler)(void);
} Route;

mindvault_app_t* mindvault_create();
void mindvault_add_route(mindvault_app_t *app, const char *path, void (*handler)(void));
void mindvault_run(mindvault_app_t *app, int port);
void mindvault_init(mindvault_app_t *app);

#endif
