CC = gcc
CFLAGS ?= -g -Wall -Wextra -std=c99 -w -lm

all:
	$(CC) $(CFLAGS) sparce_matrix.c vector.c main.c -o main

main: main.o  vector.o sparce_matrix.o
	${CC} -o main main.o  vector.o sparce_matrix.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: vector.c vector.o sparce_matrix.c sparce_matrix.o
	${CC} ${CFLAGS} -c  vector.c sparce_matrix.c

clean: 
	rm -rf *.o main