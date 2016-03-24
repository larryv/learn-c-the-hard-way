/*
    Exercise 8: If, Else-If, Else
    Print out either args or insults, depending on number of args.
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    if (argc < 2) {
        printf("You have no arguments. You suck.\n");
    } else if (argc == 2) {
        printf("You only have one argument. You suck.\n");
    } else if (argc < 12) {
        // If argc is odd, then the number of user-provided args is
        // even, and vice versa.
        if (argc % 2 == 1) {
            printf("You provided an even number of arguments:\n");
        } else {
            printf("You provided an odd number of arguments:\n");
        }

        printf("%s", argv[1]);
        for (i = 2; i < argc; i++) {
            printf(" %s", argv[i]);
        }
        printf("\n");
    } else {
        printf("You have too many arguments. You suck.\n");
    }

    return 0;
}
