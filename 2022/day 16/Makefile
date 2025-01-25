CC	= gcc
CFLAGS	= -g -Wall
PROGS	= part1 part2

all:		$(PROGS)

clean:;		$(RM) $(PROGS) *.o core

part1:	part1.c list.o table.o pqueue.o
	$(CC) part1.c list.o table.o pqueue.o
	./a.exe

part2:	part2.c list.o table.o pqueue.o
	$(CC) part2.c list.o table.o pqueue.o
	./a.exe
