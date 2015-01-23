
CC=gcc

STD=-std=c99 -pedantic
WARN=-Wall
DEBUG=-g -ggdb
CFLAGS=$(STD) $(WARN) $(DEBUG)


all: parser

parser: parser.c
	$(CC) $(CFLAGS) parser.c -o $@

