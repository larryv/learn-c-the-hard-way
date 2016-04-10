/*
    Exercise 12: Sizes and Arrays
    Print the sizes of various data types.
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    int areas[] = { 10, 12, 13, 14, 20 };
    char name[] = "Zed";
    char full_name[] = {
        'Z', 'e', 'd',
        ' ', 'A', '.', ' ',
        'S', 'h', 'a', 'w', '\0'
    };

    printf("The size of an int: %zu\n", sizeof(int));
    printf("The size of areas (int[]): %zu\n", sizeof(areas));
    printf("The number of ints in areas: %zu\n",
            sizeof(areas) / sizeof(int));
    printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);

    printf("The size of a char: %zu\n", sizeof(char));
    printf("The size of name (char[]): %zu\n", sizeof(name));
    printf("The number of chars: %zu\n", sizeof(name) / sizeof(char));

    printf("The size of full_name (char[]): %zu\n", sizeof(full_name));
    printf("The number of chars: %zu\n",
            sizeof(full_name) / sizeof(char));

    printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

    return 0;
}
