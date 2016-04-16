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

CFLAGS := -Wall -g

exercises := 1 3 7 8 9 10 11 12 13 14 15
exercises := $(exercises:%=ex%)

.PHONY: all clean
all: $(exercises)
clean:
	rm -fR $(exercises) $(exercises:%=%.dSYM)
