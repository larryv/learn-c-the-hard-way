/*
    Exercise 14: Writing and Using Functions
    Print each argument's letters and their decimal representations.
*/

#include <stdio.h>
#include <ctype.h>

void print_letters(char arg[])
{
    int i = 0;

    for (i = 0; arg[i] != '\0'; i++) {
        char ch = arg[i];

        if (isalpha(ch) || isblank(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

void print_arguments(int argc, char *argv[])
{
    int i = 0;

    for (i = 0; i < argc; i++) {
        print_letters(argv[i]);
    }
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
