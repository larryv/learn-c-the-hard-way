/*
    Exercise 9: While-Loop and Boolean Expressions
    Print various integer sequences.
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    printf("Nonnegative, ascending:");
    while (i < 10) {
        printf(" %d", i);
        i++;
    }

    printf("\n");
    return 0;
}
