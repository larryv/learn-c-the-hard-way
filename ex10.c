/*
    Exercise 10: Switch Statements
    Prints each of its arguments' letters and whether it's a vowel.
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you abort a program
        return 1;
    }

    int i = 0;
    for (i = 0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];

        printf("argv[1][%d]: '%c' is ", i, letter);
        switch (letter) {
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'o':
            case 'O':
            case 'u':
            case 'U':
                printf("a vowel");
                break;

            case 'y':
            case 'Y':
                if (i > 2) {
                    // it's only sometimes Y
                    printf("a vowel");
                }
                break;

            default:
                printf("not a vowel");
        }
        printf("\n");
    }

    return 0;
}
