# Exercises from _Learn C the Hard Way_ #

These are implementations of exercises from Zed Shaw’s [_Learn C the
Hard Way_, 1st edition][informit] (print ISBN 978-0-321-88492-3, ebook
ISBN 978-0-13-312441-5). Page numbers in files and commit messages are
from the print version. As of 14 February 2016, an [older beta
edition][online] is freely available online, although it differs
somewhat from the published book.

Building the code requires Make and a reasonable C99 compiler at `cc`.

    $ make ex17
    $ make ex5 ex29 ex43
    $ make all

If desired, a custom compiler and options can be specified explicitly.

    $ make CC=/opt/local/bin/clang-3.7 ex31
    $ make CFLAGS=-Weverything ex2
    $ make CC=gcc CFLAGS=-std=gnu99 ex47

Deleting build products works as one might expect.

    $ make clean

  [informit]: http://www.informit.com/store/learn-c-the-hard-way-practical-exercises-on-the-computational-9780321884923
    ("Learn C the Hard Way" on InformIT)
  [online]: http://c.learncodethehardway.org/book
    ("Learn C the Hard Way" online)
