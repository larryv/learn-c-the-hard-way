/*
    Exercise 10: Switch Statements
    Prints each of its arguments' letters and whether it's a vowel.
*/

#include <ctype.h>
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
    char letter = '\0';

    for (i = 1; i < argc; i++) {
        for (j = 0, letter = argv[i][j]; letter != '\0'; letter = argv[i][++j]) {
            printf("argv[%d][%d]: '%c' is ", i, j, letter);
            switch (tolower(letter)) {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                    printf("a vowel");
                    break;

                case 'y':
                    if (j > 2) {
                        // it's only sometimes Y
                        printf("a vowel");
                        break;
                    }
                    // fallthrough

                default:
                    printf("not a vowel");
            }
            printf("\n");
        }
    }

    return 0;
}
