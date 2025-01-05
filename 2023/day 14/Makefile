CC	= gcc
CFLAGS	= -g -Wall
PROGS	= part1 part2

all:		$(PROGS)

clean:;		$(RM) $(PROGS) *.o core

part1:	part1.c
	$(CC) part1.c
	./a.exe

part2:	part2.c table.o
	$(CC) part2.c table.o
	./a.exe
