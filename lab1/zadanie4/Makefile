CFLAGS=-Wall -fsanitize=address,undefined
LDFLAGS=-fsanitize=address,undefined

.PHONY: all clean

all: main

main: sop-bib-stage0.c
	gcc ${CFLAGS} ${LDFLAGS} sop-bib-stage0.c -o main

clean:
	rm -f main
