CC = gcc
CFLAGS = -Wall -g
INCLUDE = -I./include
SRC = src/db.c src/btree.c src/auth.c
OBJ = db

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ) $(INCLUDE) -lm

clean:
	rm -f $(OBJ) test.mv test.idx

.PHONY: all clean
