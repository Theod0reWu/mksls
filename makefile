ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: ls.o main.o
	$(CC) -o program ls.o main.o

main.o: main.c ls.h
	$(CC) -c main.c
ls.o: ls.c ls.h
	$(CC) -c ls.c
run:
	./program

clean:
	rm*.o
