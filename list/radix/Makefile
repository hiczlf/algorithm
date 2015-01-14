
CC=gcc

STD=-std=c99 -pedantic
WARN=-Wall
DEBUG=-g -ggdb
CFLAGS=$(STD) $(WARN) $(DEBUG)


all: radix

radix: radix.c list.c list.h
	$(CC) $(CFLAGS) radix.c list.c -o $@

