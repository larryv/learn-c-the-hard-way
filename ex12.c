/*
    Exercise 12: Sizes and Arrays
    Print the sizes of various data types.
*/

#include <stdio.h>

#define BYTE_OR_BYTES(n) (sizeof(n) == 1 ? "byte" : "bytes")

int main(int argc, char *argv[])
{
    int areas[] = { 10, 12, 13, 14, 20 };
    char name[] = "Zed";
    char full_name[] = {
        'Z', 'e', 'd',
        ' ', 'A', '.', ' ',
        'S', 'h', 'a', 'w', '\0'
    };

    printf("The size of an int: %zu %s\n",
            sizeof(int), BYTE_OR_BYTES(int));
    printf("The size of \"areas\" (int[%zu]): %zu %s\n",
            sizeof(areas) / sizeof(int),
            sizeof(areas),
            BYTE_OR_BYTES(areas));
    printf("The first area is %d; the second is %d.\n",
            areas[0],
            areas[1]);

    printf("The size of a char: %zu %s\n",
            sizeof(char),
            BYTE_OR_BYTES(char));
    printf("The size of \"name\" (char[%zu]): %zu %s\n",
            sizeof(name) / sizeof(char),
            sizeof(name),
            BYTE_OR_BYTES(name));
    printf("\"name\" is \"%s\"\n",
            name);

    printf("The size of \"full_name\" (char[%zu]): %zu %s\n",
            sizeof(full_name) / sizeof(char),
            sizeof(full_name),
            BYTE_OR_BYTES(full_name));
    printf("\"full_name\" is \"%s\"\n",
            full_name);

    return 0;
}
