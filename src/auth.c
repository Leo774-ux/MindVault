#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "db.h"

int check_permission(int required_level) {
    if (db.permission_level >= required_level) {
        return 1;
    }
    printf("Access denied. Required level: %d, Current level: %d\n", required_level, db.permission_level);
    return 0;
}

void set_security_level(int level) {
    if (level >= 0 && level <= 3) {
        db.permission_level = level;
    }
}
