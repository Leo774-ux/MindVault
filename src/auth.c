#include <stdio.h>
#include <time.h>
#include "auth.h"

static AuthLevel current_level = AUTH_GUEST;

void auth_set_level(AuthLevel level) {
    current_level = level;
}

AuthLevel auth_get_level(void) {
    return current_level;
}

int auth_check(AuthLevel required, const char *operation) {
    if (current_level < required) {
        time_t now = time(NULL);
        char *time_str = ctime(&now);
        time_str[24] = '\0';
        fprintf(stderr,
            "\nSECURITY ALERT\n"
            "Time: %s\nOperation: %s\nRequired: %s\nCurrent: %s\nAction: DENIED\n\n",
            time_str, operation,
            required == AUTH_GUEST ? "GUEST" : required == AUTH_USER ? "USER" : "ADMIN",
            current_level == AUTH_GUEST ? "GUEST" : current_level == AUTH_USER ? "USER" : "ADMIN");
        return -1;
    }
    return 0;
}
