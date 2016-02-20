# Exercise 2: Using Makefiles to Build
# A makefile to build the other exercises.

CFLAGS=-Wall -g

all: ex1

clean:
	rm -f ex1
