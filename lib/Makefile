CC	= gcc
CFLAGS	= -g -Wall
PROGS	= pqueue.c list.c

all:		$(PROGS)

clean:;		$(RM) $(PROGS) *.o core

list:	list.c list.h
	$(CC) -c list.c

pqueue:	pqueue.c pqueue.h
	$(CC) -c pqueue.c

table:	table.c table.h
	$(CC) -c table.c

map:	map.c map.h list.o
	$(CC) -c map.c