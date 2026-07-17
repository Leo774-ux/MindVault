#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "db.h"

char cmd[256];

int main() {
    printf("MindVault Database System\n");
    printf("Type 'help' for available commands.\n");
    db_init();

    while (1) {
        printf("mindvault> ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) break;
        cmd[strcspn(cmd, "\n")] = 0;

        if (strlen(cmd) == 0) continue;

        int argc = 0;
        char *argv[32];
        char *token = strtok(cmd, " ");
        while (token != NULL && argc < 32) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }

        if (argc == 0) continue;

        if (strcmp(argv[0], "open") == 0) {
            cmd_open(argc, argv);
        } else if (strcmp(argv[0], "insert") == 0) {
            cmd_insert(argc, argv);
        } else if (strcmp(argv[0], "query") == 0) {
            cmd_query(argc, argv);
        } else if (strcmp(argv[0], "delete") == 0) {
            cmd_delete(argc, argv);
        } else if (strcmp(argv[0], "status") == 0) {
            cmd_status(argc, argv);
        } else if (strcmp(argv[0], "setlevel") == 0) {
            cmd_setlevel(argc, argv);
        } else if (strcmp(argv[0], "exit") == 0) {
            printf("Exiting MindVault, Goodbye!\n");
            break;
        } else if (strcmp(argv[0], "help") == 0) {
            cmd_help(argc, argv);
        } else {
            printf("Unknown command: %s\n", argv[0]);
            printf("Type 'help' for available commands.\n");
        }
    }

    db_close();
    return 0;
}
