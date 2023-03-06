# Makefile
# Lab04
CC=gcc
CFLAGS = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra
LINK = -Wl,--wrap=free 
OBJECTS = test_list list.o


all: test_list

test: all
	./test_list

test_list: test_list.c list.o
	$(CC) $(CFLAGS) $(LINK) test_list.c -o $(OBJECTS) -lcmocka

list.o: list.c list.h list_internal.h
	$(CC) $(CFLAGS) -c list.c

clean:
	rm -vf *.o test_list