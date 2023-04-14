# Makefile
# Assign6
CC=gcc
CFLAGS = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra
OBJECTS = process_a process_b

all: $(OBJECTS)

# Run Options
# $(which kill) --signal SIGINT -q 41477
# enable -n kill
# kill --signal SIGINT -q 999999 41477
# env kill --signal -SIGINT -q <proc A pid> <proc B pid>

process_a: process_a.c
	$(CC) $(CFLAGS) -o process_a process_a.c


process_b: process_b.c
	$(CC) $(CFLAGS) -o process_b process_b.c


clean:
	rm -vf *.o $(OBJECTS)
