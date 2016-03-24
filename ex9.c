/*
    Exercise 9: While-Loop and Boolean Expressions
    Print various integer sequences.
*/

#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    long n = 0;
    int seq[10] = {0};

    printf("Nonnegative, ascending:");
    i = 0;
    while (i < 10) {
        printf(" %d", i);
        i++;
    }

    printf(" ...\nNonnegative, descending: ...");
    i = 9;
    while (i >= 0) {
        printf(" %d", i);
        i--;
    }

    printf("\nEven:");
    i = 0;
    while (i < 10) {
        printf(" %d", i * 2);
        i++;
    }

    printf(" ...\nOdd:");
    i = 0;
    while (i < 10) {
        printf(" %d", i * 2 + 1);
        i++;
    }

    printf(" ...\nSquares:");
    i = 0;
    while (i < 10) {
        printf(" %d", i * i);
        i++;
    }

    printf(" ...\nCubes:");
    i = 0;
    while (i < 10) {
        printf(" %d", i * i * i);
        i++;
    }

    printf(" ...\nPowers of 10:");
    n = 1;
    printf(" %ld", n);
    i = 1;
    while (i < 10) {
        n *= 10;
        printf(" %ld", n);
        i++;
    }

    printf(" ...\nPowers of 2:");
    n = 1;
    printf(" %ld", n);
    i = 1;
    while (i < 10) {
        n *= 2;
        printf(" %ld", n);
        i++;
    }

    printf(" ...\nFibonacci:");
    seq[0] = 0;
    seq[1] = 1;
    printf(" %d %d", seq[0], seq[1]);
    i = 2;
    while (i < 10) {
        seq[i] = seq[i - 1] + seq[i - 2];
        printf(" %d", seq[i]);
        i++;
    }

    printf(" ...\nLucas:");
    seq[0] = 2;
    seq[1] = 1;
    printf(" %d %d", seq[0], seq[1]);
    i = 2;
    while (i < 10) {
        seq[i] = seq[i - 1] + seq[i - 2];
        printf(" %d", seq[i]);
        i++;
    }

    printf(" ...\nPell:");
    seq[0] = 0;
    seq[1] = 1;
    printf(" %d %d", seq[0], seq[1]);
    i = 2;
    while (i < 10) {
        seq[i] = 2 * seq[i - 1] + seq[i - 2];
        printf(" %d", seq[i]);
        i++;
    }

    printf(" ...\nCatalan:");
    seq[0] = 1;
    printf(" %d", seq[0]);
    i = 0;
    while (i < 9) {
        seq[i + 1] = lround(seq[i] * (4 * i + 2) / (double)(i + 2));
        printf(" %d", seq[i + 1]);
        i++;
    }

    printf(" ...\n");
    return 0;
}
