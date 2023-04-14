# Makefile
# Assign6
CC=gcc
CFLAGS = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra
OBJECTS = process_a process_b

all: $(OBJECTS)

# Run Options
# kill -2 -q <proc A pid> <proc B pid>

process_a: process_a.c
	$(CC) $(CFLAGS) -o process_a process_a.c


process_b: process_b.c
	$(CC) $(CFLAGS) -o process_b process_b.c


clean:
	rm -vf *.o $(OBJECTS)
