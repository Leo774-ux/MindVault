#include <stdio.h>
#include "mindvault.h"

int main() {
    printf("MindVault CLI\n");
    printf("=============\n");
    mv_init();
    mv_open("/tmp/test.db");
    mv_insert(1, "Hello World!");
    Record* rec = mv_query(1);
    if (rec) printf("Query: %s\n", rec->data);
    mv_close();
    return 0;
}
