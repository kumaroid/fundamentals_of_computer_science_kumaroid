CC = gcc
CFLAGS ?= -g -Wall -Wextra -std=c99 -w -lm

all:
	$(CC) $(CFLAGS)  vector_str.c main.c -o main

main: main.o  vector_str.o 
	${CC} -o main main.o  vector_str.o 

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: vector_str.c vector_str.o  
	${CC} ${CFLAGS} -c  vector_str.c 

clean: 
	rm -rf *.o main