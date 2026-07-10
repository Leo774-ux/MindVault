#ifndef BTREE_H
#define BTREE_H

#include "db.h"

void btree_init(Database *db);
int  btree_insert(Database *db, int offset, int length);
void btree_delete(int offset);

#endif
