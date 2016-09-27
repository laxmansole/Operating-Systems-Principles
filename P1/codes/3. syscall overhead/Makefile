CC = gcc
#OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)


SRC=$(wildcard *.c)

PROGS=$(patsubst %.c,%,$(SRC))

all:$(PROGS)

%: %.c
	${CC} -o $@ $<


clean:
	find . -name '*.c' -o -name 'Makefile' -o -name 'script.sh' -prune -o -type f -exec rm {} \;
