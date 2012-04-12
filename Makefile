CC := gcc
CFLAGS := -Wall -g -std=c99

ex := $(patsubst %.c,%,$(wildcard *.c))

all: $(ex)

clean:
	rm -f $(ex)
	rm -fR *.dSYM
