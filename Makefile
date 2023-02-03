CC=gcc -Wall
SRC=$(wildcard *.c)
HEAD=$(wildcard *.h)
OBJ=$(SRC:.c=.o)
RM=rm -f prog
PROG=prog

all : $(PROG)
.c.o :
	$(CC) -c $^ -o $@
prog : $(OBJ)
	@$(CC) $^ -o $@
.PHONY: clean
clean :
	$(RM) $(OBJ)