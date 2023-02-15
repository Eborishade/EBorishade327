# Makefile
# Lab03
CC=gcc
CFLAGS = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra
OBJECTS = malloc.o malloc_test.o

all: malloc_test

malloc_test: malloc.o malloc_test.o
	$(CC) $(CFLAGS) -o malloc_test $(OBJECTS)


malloc_test.o: malloc_test.c malloc.h
	$(CC) $(CFLAGS) -c malloc_test.c


malloc.o: malloc.c malloc.h
	$(CC) $(CFLAGS) -c malloc.c

clean:
	rm -vf *.o 