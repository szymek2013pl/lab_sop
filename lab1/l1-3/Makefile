CFLAGS=-Wall -fsanitize=address,undefined
LDFLAGS=-fsanitize=address,undefined

.PHONY: all clean

all: l1-3

l1-3: l1-3.c
	gcc ${CFLAGS} ${LDFLAGS} l1-3.c -o l1-3

clean:
	rm -f l1-3
