
CC=gcc
STD=-std=c99 -pedantic
WARN=-Wall
DEBUG=-g -ggdb
CFLAGS=$(STD) $(WARN) $(DEBUG)

TARGET=p2i
SRCS = p2i.c stack.c



all: $(TARGET)

$(TARGET): $(SRCS)
	gcc $(CFLAGS) -o $@ $+

clean:
	rm -f a.out $(TARGET)
