CC=gcc

CFLAGS_REL=-Wall -ansi -O0
CFLAGS_DBG=-Wall -ansi -DDEBUG -g -O0 -ggdb3 -pedantic
CFLAGS_SML=-Wall -ansi -Os

OBJS=asm.c error.c parse.c code.c symbol.c
OUT=-o asm

asmcompile: $(OBJS)
	$(CC) $(CFLAGS_REL) $(OUT) $^

asmlink: asm.o
	gcc -o asm error.o parse.o code.o

asm: asmlink

small: $(OBJS)
	$(CC) $(CFLAGS_SML) $(OUT) $^ 

debug: $(OBJS)
	$(CC) $(CFLAGS_DBG) $(OUT) $^

clean:
	rm -f asm *.o
