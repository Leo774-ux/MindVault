#include <stdlib.h>
#include <stdlib.h>   // ✅ 修复 atoi 未声明
#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "db.h"
#include "auth.h"

void cmd_help(int argc, char *argv[]) {
    printf("Available commands:\n");
    printf("  open <path>     - Open database file\n");
    printf("  insert <id> <data> - Insert record\n");
    printf("  query <id>      - Query record by ID\n");
    printf("  delete <id>     - Delete record by ID\n");
    printf("  status          - Show database status\n");
    printf("  setlevel <0-3>  - Set security level\n");
    printf("  exit            - Exit program\n");
    printf("  help            - Show this help\n");
}

void cmd_open(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: open <path>\n");
        return;
    }
    if (db_open(argv[1]) == 0) {
        printf("Database opened successfully.\n");
    } else {
        printf("Failed to open database.\n");
    }
}

void cmd_insert(int argc, char *argv[]) {
    if (!check_permission(1)) return;
    if (argc < 3) {
        printf("Usage: insert <id> <data>\n");
        return;
    }
    int id = atoi(argv[1]);
    if (db_insert(id, argv[2]) == 0) {
        printf("Record inserted.\n");
    } else {
        printf("Failed to insert record.\n");
    }
}

void cmd_query(int argc, char *argv[]) {
    if (!check_permission(1)) return;
    if (argc < 2) {
        printf("Usage: query <id>\n");
        return;
    }
    int id = atoi(argv[1]);
    Record *rec = db_query(id);
    if (rec != NULL) {
        printf("ID: %d, Data: %s\n", rec->id, rec->data);
    } else {
        printf("Record not found.\n");
    }
}

void cmd_delete(int argc, char *argv[]) {
    if (!check_permission(2)) return;
    if (argc < 2) {
        printf("Usage: delete <id>\n");
        return;
    }
    int id = atoi(argv[1]);
    if (db_delete(id) == 0) {
        printf("Record deleted.\n");
    } else {
        printf("Failed to delete record.\n");
    }
}

void cmd_status(int argc, char *argv[]) {
    if (!check_permission(0)) return;
    db_status();
}

void cmd_setlevel(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: setlevel <0-3>\n");
        return;
    }
    int level = atoi(argv[1]);
    set_security_level(level);
    printf("Security level set to %d.\n", level);
}
