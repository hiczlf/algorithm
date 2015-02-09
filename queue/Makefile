
CC=gcc

STD=-std=c99 -pedantic
WARN=-Wall
DEBUG=-g -ggdb
CFLAGS=$(STD) $(WARN) $(DEBUG)


all: queue

queue: queue.c
	$(CC) $(CFLAGS) queue.c -o $@

