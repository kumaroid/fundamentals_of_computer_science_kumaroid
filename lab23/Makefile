CC ?= gcc 
CFLAGS ?= -g -Werror -pedantic
main: main.o tree.o
	${CC} -o main main.o tree.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: tree.c tree.o
	${CC} ${CFLAGS} -c tree.c

clean: 
	rm -rf *.o main