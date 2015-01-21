
CC=gcc

STD=-std=c99 -pedantic
WARN=-Wall
DEBUG=-g -ggdb
CFLAGS=$(STD) $(WARN) $(DEBUG)


all: cursor

cursor: cursor.c cursor.h
	$(CC) $(CFLAGS) cursor.c -o $@

