CC = gcc

SRC=$(wildcard *.c)

PROGS=$(patsubst %.c,%,$(SRC))

all:$(PROGS)

%: %.c
	${CC} -o $@ $<


clean:
	find . -name '*.c' -o -name 'Makefile' -o -name 'script.sh' -prune -o -type f -exec rm {} \;
