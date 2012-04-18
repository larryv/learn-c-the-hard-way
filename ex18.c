#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

/* Our old friend die() from ex17. */
void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        fprintf(stderr, "ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);
typedef int *(*sort_cb)(int *numbers, int count, compare_cb cmp);

/*
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if (!target) die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count; ++i) {
        for (j = 0; j < count - 1; ++j) {
            if (cmp(target[j], target[j + 1]) > 0) {
                temp = target[j + 1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

/* Heapsort implementation from CLRS, 3rd ed. */

/* Heap primitives */
#define PARENT(i) (((i) - 1) >> 1)
#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) + 1) << 1)

struct Heap {
    int *array;
    size_t len;
    size_t heap_sz;
};

int max_heapify(struct Heap *A, size_t i, compare_cb cmp)
{
    size_t l, r, largest;
    int tmp;

    if (!A || !A->array) {
        errno = EFAULT;
        return 1;
    }

    l = LEFT(i);
    r = RIGHT(i);
    largest = (l < A->heap_sz && cmp(A->array[l], A->array[i]) > 0) ? l : i;
    if (r < A->heap_sz && cmp(A->array[r], A->array[largest]) > 0)
        largest = r;
    if (largest != i) {
        tmp = A->array[i];
        A->array[i] = A->array[largest];
        A->array[largest] = tmp;
        max_heapify(A, largest, cmp);
    }
    return 0;
}

struct Heap *build_max_heap(int *input, size_t len, compare_cb cmp)
{
    struct Heap *A;
    ssize_t i;

    if (!input) {
        errno = EFAULT;
        return NULL;
    }

    if (!(A = malloc(sizeof(struct Heap))))
        die("Memory error.");
    A->array = input;
    A->heap_sz = A->len = len;
    for (i = A->len / 2 - 1; i >= 0; --i)
        max_heapify(A, i, cmp);
    return A;
}

/* Operates on a copy of the input array, not on the original. */
int *heap_sort(int *numbers, int count, compare_cb cmp)
{
    int *target, tmp;
    struct Heap *A;
    size_t i;

    if (!(target = malloc(count * sizeof(int))))
        die("Memory error.");
    memcpy(target, numbers, count * sizeof(int));

    A = build_max_heap(target, count, cmp);
    for (i = A->len - 1; i > 0; --i) {
        tmp = A->array[0];
        A->array[0] = A->array[i];
        A->array[i] = tmp;
        --A->heap_sz;
        max_heapify(A, 0, cmp);
    }
    return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if (a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/*
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, sort_cb sort, compare_cb cmp)
{
    int i = 0;
    int *sorted = sort(numbers, count, cmp);

    if (!sorted) die("Failed to sort as requested.");

    for (i = 0; i < count; ++i) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
}


int main(int argc, char **argv)
{
    if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if (!numbers) die("Memory error.");

    for (i = 0; i < count; ++i) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, bubble_sort, sorted_order);
    test_sorting(numbers, count, bubble_sort, reverse_order);
    test_sorting(numbers, count, bubble_sort, strange_order);
    test_sorting(numbers, count, heap_sort, sorted_order);
    test_sorting(numbers, count, heap_sort, reverse_order);
    test_sorting(numbers, count, heap_sort, strange_order);

    free(numbers);

    return 0;
}
