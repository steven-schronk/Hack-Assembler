CC=gcc
CFLAGS=-Wall
asm: asm.o parse.o error.o

clean:
	rm -f asm asm.o parse.o error.o

