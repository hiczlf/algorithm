
CC=gcc

STD=-std=c99 -pedantic
WARN=-Wall
DEBUG=-g -ggdb
CFLAGS=$(STD) $(WARN) $(DEBUG)


all: cursor

radix: cursor.c cursor.h
	$(CC) $(CFLAGS) radix.c -o $@

