# Exercise 2: Using Makefiles to Build
# A makefile to build the other exercises.
#
# I'm trying to keep this reasonably portable. I've kicked the tires on:
# - OS X 10.11 (El Capitan)
#   - GNU Make 3.81
#   - BSD Make from Xcode 4.2 ("version 24")
#   - bmake 20151201

# Never read SHELL from the environment
# (http://www.gnu.org/software/make/manual/html_node/Makefile-Basics.html).
SHELL := /bin/sh

CFLAGS += -Wall -g

.PHONY: all clean
all: ex1 ex3
clean:
	rm -fR ex1 ex1.dSYM ex3 ex3.dSYM
