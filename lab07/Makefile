# Makefile
# Forks
CC=gcc
CFLAGS = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra
OBJECTS = fork1 fork2 fork3

all: $(OBJECTS)

fork1: fork1.c
	$(CC) $(CFLAGS) fork1.c -o fork1


fork2: fork2.c
	$(CC) $(CFLAGS) fork2.c -o fork2


fork3: fork3.c
	$(CC) $(CFLAGS) fork3.c -o fork3


clean:
	rm -vf *.o $(OBJECTS)
