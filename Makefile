# Exercise 2: Using Makefiles to Build
# A makefile to build the other exercises.
#
# I'm trying to keep this reasonably portable. I've kicked the tires on:
# - OS X 10.11 (El Capitan)
#   - GNU Make 3.81
#   - BSD Make as distributed by Apple with Xcode 4.2 ("version 24")
#   - bmake 20151201
#
# References:
#   [*] http://www.gnu.org/software/make/manual/html_node/Makefile-Basics.html

# Never read SHELL from the environment. [*]
SHELL = /bin/sh

# Clear out unnecessary suffix rules. [*]
.SUFFIXES:
.SUFFIXES: .c

CFLAGS += -Wall -g

.PHONY: all clean

all: ex1

clean:
	rm -f ex1
