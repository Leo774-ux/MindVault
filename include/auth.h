#ifndef AUTH_H
#define AUTH_H

typedef enum {
    AUTH_GUEST = 0,
    AUTH_USER  = 1,
    AUTH_ADMIN = 2
} AuthLevel;

void auth_set_level(AuthLevel level);
AuthLevel auth_get_level(void);
int auth_check(AuthLevel required, const char *operation);

#endif
