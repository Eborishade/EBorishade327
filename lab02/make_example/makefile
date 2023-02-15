CC=gcc
OBJECTS= edit main.o kbd.o command.o display.o \
		insert.o search.o files.o utils.o

all : edit

edit : $(OBJECTS)
		$(CC) -o $(OBJECTS)

main.o : main.c defs.h
	 $(CC) -c main.c
kbd.o : kbd.c defs.h command.h
	 $(CC) -c kbd.c
command.o : command.c defs.h command.h
	 $(CC) -c command.c
display.o : display.c defs.h buffer.h
	 $(CC) -c display.c
insert.o : insert.c defs.h buffer.h
	 $(CC) -c insert.c
search.o : search.c defs.h buffer.h
	 $(CC) -c search.c
files.o : files.c defs.h buffer.h command.h
	 $(CC) -c files.c
utils.o : utils.c defs.h
	 $(CC) -c utils.c
	 
clean :
	rm -vf $(OBJECTS)