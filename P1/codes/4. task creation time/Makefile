CC = gcc
#OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)


SRC=$(wildcard *.c)

PROGS=$(patsubst %.c,%,$(SRC))

all:$(PROGS)

%: %.c
	${CC} -o $@ $< -pthread


clean:
	find . -name '*.c' -o -name 'Makefile' -prune -o -type f -exec rm {} \;
