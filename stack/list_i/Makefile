
CC=gcc
STD=-std=c99 -pedantic
WARN=-Wall
DEBUG=-g -ggdb
CFLAGS=$(STD) $(WARN) $(DEBUG)

TARGET=stack
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)



all: $(TARGET)

$(TARGET): $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET) .depend


depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MMD $^ -MF  ./.depend;
-include .depend
