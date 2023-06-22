CC = gcc
CFLAGS ?= -g -Wall -Wextra -std=c99 -w -lm -Wformat=2

all:
	$(CC) $(CFLAGS) serialization.c computer.c main.c -o main

main: main.o computer.o serialization.o
	${CC} -o main main.o computer.o converter.o serialization.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: computer.c computer.o converter.c converter.o serialization.c serialization.o
	${CC} ${CFLAGS} -c computer.c converter.c

converter:
	${CC} ${CFLAGS} computer.c converter.c serialization.c -o conv

#Use this command, and run: ./a.out [number_of_students], then give filename wich will record
generate:
	${CC} ${CFLAGS} computer.c serialization.c make_test.c -o gener

clean: 
	rm -rf *.bin *.txt *.o main