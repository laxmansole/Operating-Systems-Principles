CC = gcc
OPT = -std=c99
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) 


SRC=$(wildcard *.c)

PROGS=$(patsubst %.c,%,$(SRC))

all:$(PROGS)

%: %.c
	${CC} -o $@ $<


clean:
	find . -name '*.c' -o -name 'Makefile' -prune -o -type f -exec rm {} \;
