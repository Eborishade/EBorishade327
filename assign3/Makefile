# Makefile
# Assign3: compare static vs dynamic library linking (looking at file size)
CC=gcc
CFLAGS = -g -ggdb -gdwarf-4 -O0 -Wall -Wextra
OBJ = compare_static compare_dynamic compare.o
executables = compare_static compare_dynamic

all: compare

compare: $(OBJ)
# list file sizes of executables (ls -hs) (stat -c%s [file1]) or (size [file])
	stat -c%s $(executables)

compare_static: compare.o
	$(CC) $(CFLAGS) -static -o compare_static compare.o


compare_dynamic: compare.o 
#gcc compiles using dynamic library linking by default
	$(CC) $(CFLAGS) -o compare_dynamic compare.o


compare.o: compare.c
	$(CC) $(CFLAGS) -c compare.c


clean:
	rm -vf *.o compare_*