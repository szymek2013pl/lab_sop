CFLAGS=-Wall -fsanitize=address,undefined
LDFLAGS=-fsanitize=address,undefined

.PHONY: all clean

all: l1-2

l1-2: l1-2.c
	gcc ${CFLAGS} ${LDFLAGS} l1-2.c -o l1-2

clean:
	rm -f l1-2