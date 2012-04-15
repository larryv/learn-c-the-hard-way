#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define REALLOC_FACTOR 2

struct Stack {
    int *contents;
    int capacity;
    int pos;
};

struct Stack *create_stack(int capacity)
{
    struct Stack *s;

    if (!(s = malloc(sizeof(struct Stack))))
        return NULL;
    if (!(s->contents = malloc(capacity * sizeof(int))))
        return NULL;
    s->capacity = capacity;
    s->pos = 0;
    return s;
}

int is_empty(struct Stack *stack)
{
    return !stack->pos;
}

/*
 * Only accepts non-negative integers, because pop uses -1 for error.
 * Return a pointer to the stack itself, or NULL on error.
 */
struct Stack *push(struct Stack *stack, int obj)
{
    if (!stack || obj < 0)
        return NULL;

    if (stack->pos == stack->capacity) {
        int *new = realloc(stack->contents, stack->capacity * REALLOC_FACTOR);
        if (!new)
            return NULL;
        stack->contents = new;
        stack->capacity *= REALLOC_FACTOR;
    }
    stack->contents[stack->pos++] = obj;
    return stack;
}

/* Return -1 on error. */
int pop(struct Stack *stack)
{
    if (!stack || is_empty(stack))
        return -1;
    return stack->contents[--stack->pos];
}

/* Return -1 on error. */
int peek(struct Stack *stack)
{
    if (!stack || is_empty(stack))
        return -1;
    return stack->contents[stack->pos - 1];
}

void destroy_stack(struct Stack *stack)
{
    free(stack->contents);
    free(stack);
}

int main(int argc, const char *argv[])
{
    struct Stack *s;

    if (!(s = create_stack(5)))
        return 1;

    /* new stack should be empty */
    assert(is_empty(s));

    /* pushing should make stack not empty */
    push(s, 13);
    assert(!is_empty(s));

    /* popping should produce the expected result */
    assert(13 == pop(s));
    assert(is_empty(s));

    /* popping from an empty stack fails */
    assert(-1 == pop(s));

    /* peeking does not pop */
    push(s, 69);
    assert(69 == peek(s));
    assert(!is_empty(s));

    destroy_stack(s);
    return 0;
}
