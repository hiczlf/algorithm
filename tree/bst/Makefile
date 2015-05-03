
CC=gcc
STD=-std=c99 -pedantic
WARN=-Wall
DEBUG=-g -ggdb
CFLAGS=$(STD) $(WARN) $(DEBUG)

TARGET=tree
SRCS = bst_tree.c



all: $(TARGET)

$(TARGET): $(SRCS)
	gcc $(CFLAGS) -o $@ $+

clean:
	rm -f a.out $(TARGET)
