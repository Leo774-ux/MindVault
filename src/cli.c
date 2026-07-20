#include "mindvault.h"
#include <stdio.h>
#include <stdlib.h>

void hello_handler() {
    printf("Handling /hello\n");
}

int main() {
    mindvault_app_t *app = mindvault_create();
    mindvault_add_route(app, "/hello", hello_handler);
    mindvault_run(app, 8080);
    return 0;
}
