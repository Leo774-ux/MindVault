#include "mindvault.h"
#include <microhttpd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROUTES 100
static Route routes[MAX_ROUTES];
static int route_count = 0;

static enum MHD_Result answer_to_connection(
    void *cls,
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    const char *upload_data,
    unsigned long int *upload_data_size,
    void **con_cls
) {
    (void)cls; (void)method; (void)version; (void)upload_data; (void)upload_data_size; (void)con_cls;

    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].path, url) == 0) {
            if (routes[i].handler) routes[i].handler();
            const char *response_text = "OK";
            struct MHD_Response *response = MHD_create_response_from_buffer(
                strlen(response_text), (void*)response_text, MHD_RESPMEM_PERSISTENT);
            enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
            return ret;
        }
    }
    const char *not_found = "404 Not Found";
    struct MHD_Response *response = MHD_create_response_from_buffer(
        strlen(not_found), (void*)not_found, MHD_RESPMEM_PERSISTENT);
    enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);
    return ret;
}

void mindvault_run(mindvault_app_t *app, int port) {
    struct MHD_Daemon *daemon = MHD_start_daemon(
        MHD_USE_INTERNAL_POLLING_THREAD, port, NULL, NULL,
        &answer_to_connection, NULL, MHD_OPTION_END);
    if (!daemon) {
        fprintf(stderr, "Failed to start server on port %d\n", port);
        exit(1);
    }
    printf("Server running on port %d...\n", port);
    getchar();
    MHD_stop_daemon(daemon);
}

void mindvault_add_route(mindvault_app_t *app, const char *path, void (*handler)(void)) {
    if (route_count < MAX_ROUTES) {
        routes[route_count].path = path;
        routes[route_count].handler = handler;
        route_count++;
    }
}

void mindvault_init(mindvault_app_t *app) {
    printf("MindVault Framework Initialized (No DB Mode).\n");
}

mindvault_app_t* mindvault_create() {
    return (mindvault_app_t*)malloc(sizeof(mindvault_app_t));
}
