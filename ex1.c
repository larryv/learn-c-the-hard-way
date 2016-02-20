/*
    Exercise 1: Dust Off That Compiler
    A small demonstration of a variety of C features.
*/

#include <stdio.h>

/* This is a comment. */
int main(int argc, char *argv[])
{
    int distance = 100;

    // this is also a comment
    printf("You are %d miles away.\n", distance);

    // LCTHW extra credit
    printf("argc = %d\n", argc);
    printf("something more complex than \"%s\"\n", "hello world");
    printf("\"%s\" was written by %s.\n", "Learn C the Hard Way", "Zed Shaw");

    return 0;
}
