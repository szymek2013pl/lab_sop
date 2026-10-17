CFLAGS=-Wall -fsanitize=address,undefined
LDFLAGS=-fsanitize=address,undefined

.PHONY: all clean

all: zadanie1

zadanie1: zadanie1.c
	gcc ${CFLAGS} ${LDFLAGS} zadanie1.c -o zadanie1

clean:
	rm -f zadanie1
