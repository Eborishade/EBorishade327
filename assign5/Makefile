# Makefile
# Assign5
CC=gcc
CFLAGS = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra
OBJECTS = system_info.o

all: system_info

system_info: system_info.o
	$(CC) $(CFLAGS) -o system_info $(OBJECTS)


system_info.o: system_info.c
	$(CC) $(CFLAGS) -c system_info.c


clean:
	rm -vf *.o system_info