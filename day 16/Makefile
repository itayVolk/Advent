CC	= gcc
CFLAGS	= -g -Wall
PROGS	= part1 part2

all:		$(PROGS)

clean:;		$(RM) $(PROGS) *.o core

part1:	part1.o pqueue.o list.o
	$(CC) -o a part1.o pqueue.o list.o
	./a.exe

part2:	part2.o pqueue.o list.o
	$(CC) -o a part2.o pqueue.o list.o
	./a.exe