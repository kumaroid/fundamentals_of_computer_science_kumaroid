CC = gcc
CFLAGS ?= -g -Wall -Wextra -std=c99 -w -lm

all:
	$(CC) $(CFLAGS)  list.c main.c -o main

main: main.o  list.o 
	${CC} -o main main.o  list.o 

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: list.c list.o  
	${CC} ${CFLAGS} -c  list.c 

clean: 
	rm -rf *.o main