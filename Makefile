CC			:= gcc
CFLAGS 		:= -Wall -std=gnu11

onc_ls: 	lists.o onc_ls.o printer.o

onc_ls.o:	onc_ls.c lists.h
lists.o:	lists.c lists.h
printer.o:	printer.c printer.h lists.h
