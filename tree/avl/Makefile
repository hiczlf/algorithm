
CC=gcc
STD=-std=c99 -pedantic
WARN=-Wall
DEBUG=-g -ggdb
CFLAGS=$(STD) $(WARN) $(DEBUG)

TARGET=avl
SRCS = avl.c



all: $(TARGET)

$(TARGET): $(SRCS)
	gcc $(CFLAGS) -o $@ $+

clean:
	rm -f a.out $(TARGET)
