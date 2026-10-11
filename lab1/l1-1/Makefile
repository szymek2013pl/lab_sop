CFLAGS=-Wall -fsanitize=address,undefined
LDFLAGS=-fsanitize=address,undefined

.PHONY: all clean

all: l1-1

l1-1: l1-1.c
	gcc ${CFLAGS} ${LDFLAGS} l1-1.c -o l1-1

clean:
	rm -f l1-1
