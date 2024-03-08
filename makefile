CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=grades.c grades.h
EXEC=libgrades.so
RM=-rf *.o

$(EXEC) : libgrades.o
	$(CCLINK) -shared grades.o -o $(EXEC)

grades.o : $(OBJS)
	$(CC) -c -fpic grades.c -linked-list -L.

clean :
	rm $(RM)