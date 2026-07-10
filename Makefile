CC = gcc
CFLAGS = -Wall -g -I./include
SRC = src/db.c src/btree.c src/auth.c
OBJ = db

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ) -lm

clean:
	rm -f $(OBJ) *.mv *.idx

.PHONY: all clean
