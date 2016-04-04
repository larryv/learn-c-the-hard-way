/*
    Exercise 10: Switch Statements
    Prints each of its arguments' letters and whether it's a vowel.
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("ERROR: You need at least one argument.\n");
        // this is how you abort a program
        return 1;
    }

    int i = 0;
    int j = 0;

    for (i = 1; i < argc; i++) {
        for (j = 0; argv[i][j] != '\0'; j++) {
            char letter = argv[i][j];

            printf("argv[%d][%d]: '%c' is ", i, j, letter);
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
                    if (j > 2) {
                        // it's only sometimes Y
                        printf("a vowel");
                    }
                    break;

                default:
                    printf("not a vowel");
            }
            printf("\n");
        }
    }

    return 0;
}
