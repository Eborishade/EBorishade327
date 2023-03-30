# Makefile
# Assign6
CC=gcc
CFLAGS = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra
OBJECTS = exec_env execd_pgm

all: $(OBJECTS)

run: all
	./exec_env ./execd_pgm EXECD_PGM_NAME=assign6


exec_env: exec_env.c
	$(CC) $(CFLAGS) -o exec_env exec_env.c


exec_pgm: exec_pgm.c
	$(CC) $(CFLAGS) -o exec_pgm exec_pgm.c


clean:
	rm -vf *.o $(OBJECTS)