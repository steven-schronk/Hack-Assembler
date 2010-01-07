CC=gcc
CFLAGS_REL=-Wall -ansi -O2
CFLAGS_DBG=-Wall -ansi -DDEBUG -g -O0
OBJS=asm.c error.c parse.c
OUT=-o asm

asm: $(OBJS)
	$(CC) $(CFLAGS_REL) $(OUT) $^

debug: $(OBJS)
	$(CC) $(CFLAGS_DBG) $(OUT) $^

clean:
	rm -f asm *.o
