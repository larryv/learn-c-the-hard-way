/*
    Exercise 15: Pointers, Dreaded Pointers
    Print two arrays using several methods of iteration.
*/

#include <stddef.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    size_t count = sizeof(ages) / sizeof(int);
    size_t i = 0;

    // first way using indexing
    printf("--- Index notation with arrays (forwards) ---\n");
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }
    printf("\n--- Index notation with arrays (backwards) ---\n");
    for (i = count; i > 0; i--) {
        printf("%s has %d years alive.\n", names[i - 1], ages[i - 1]);
    }

    // set up the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    printf("\n--- Offsets with pointer arithmetic (forwards) ---\n");
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name + i), *(cur_age + i));
    }
    printf("\n--- Offsets with pointer arithmetic (backwards) ---\n");
    for (i = count; i > 0; i--) {
        printf("%s is %d years old.\n",
                *(cur_name + i - 1), *(cur_age + i - 1));
    }

    // third way, pointers are just arrays
    printf("\n--- Index notation with pointers (forwards) ---\n");
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }
    printf("\n--- Index notation with pointers (backwards) ---\n");
    for (i = count; i > 0; i--) {
        printf("%s is %d years old again.\n",
                cur_name[i - 1], cur_age[i - 1]);
    }

    // fourth way with pointers in a stupid complex way
    printf("\n--- Walking with pointer arithmetic (forwards) ---\n");
    for (cur_name = names, cur_age = ages;
            (cur_age - ages) < count; cur_name++, cur_age++) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }
    printf("\n--- Walking with pointer arithmetic (backwards) ---\n");
    for (cur_name = names + count - 1, cur_age = ages + count - 1;
            cur_age >= ages; cur_name--, cur_age--) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }

    printf("\n--- Addresses ---\n");
    for (i = 0; i < count; i++) {
        printf("&names[%zu] == %p, &ages[%zu] == %p\n",
                i, names + i, i, ages + i);
    }

    return 0;
}
