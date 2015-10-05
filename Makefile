CC=gcc
CFLAGS=-I.

main: main.o cliffWorld.o
	$(CC) -o main main.o cliffWorld.o -I.

clean:
	rm -f *.o main