CC = gcc

SRC=$(wildcard *.c)

PROGS=$(patsubst %.c,%,$(SRC))

all:$(PROGS)

%: %.c
	${CC} -o $@ $< -pthread


clean:
	find . -name '*.c' -o -name 'Makefile' -prune -o -type f -exec rm {} \;
