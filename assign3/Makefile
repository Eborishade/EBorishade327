# Makefile
# Assign3
CC=gcc
CFLAGS = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra
OBJECTS = compare_static.o compare_dynamic.o compare.o

all: compare

compare: $(OBJECTS)
# do comparison


compare_static.o: compare.o
	$(CC) $(CFLAGS) -o compare_static


compare_dynamic.o: compare.o
	$(CC) $(CFLAGS) -o compare_dynamic


compare.o: compare.c
	$(CC) $(CFLAGS) -c compare.c


clean:
	rm -vf *.o 