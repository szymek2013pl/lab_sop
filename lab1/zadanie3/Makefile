CFLAGS=-Wall -fsanitize=address,undefined
LDFLAGS=-fsanitize=address,undefined

.PHONY: all clean

all: sop_venv

sop_venv: main.c
	gcc ${CFLAGS} ${LDFLAGS} main.c -o sop_venv

clean:
	rm -f sop_venv
