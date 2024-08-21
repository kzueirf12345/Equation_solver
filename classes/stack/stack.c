#include "stack.h"

Stack Stack_create(size_t elemsize, size_t capacity) {
    return (Stack){malloc(capacity * sizeof(void*)), elemsize, 0, capacity};
}

void Stack_push(Stack* stack, void* data) {
    assert(stack && "not init stack");

    if (stack->data == NULL) {
        stack->data = malloc(sizeof(data));
        stack->capacity = 1;
    } else if (stack->size + 1 >= stack->capacity) {
        stack->capacity = MAX(2 * stack->capacity, stack->size + 1);
        stack->data = realloc(stack->data, stack->capacity * sizeof(void*));
    }
    stack->data[stack->size] = malloc(stack->elemsize);
    memcpy(stack->data[stack->size], data, stack->elemsize);
    ++stack->size;
}

void* Stack_back(Stack* stack) {
    assert(stack && "not init stack");
    assert(stack->size && "stack is empty");
    return stack->data[stack->size - 1];
}

void Stack_pop(Stack* stack) {
    assert(stack && "not init stack");
    free(stack->data[--stack->size]);
}

void Stack_print(Stack* stack) {
    for (int i = 0; i < stack->size; ++i)
    {
        printf("%p ", stack->data[i]);
    }
    printf("\n");
}

void Stack_clear(Stack* stack, const int capacity)
{
    assert(stack && "stack is null");

    for (int i = 0; i < stack->size; ++i) {
        assert(stack->data[i] && "some element of stack is NULL");
        free(stack->data[i]);
    }
    free(stack->data);
    stack->size = 0;
    stack->capacity = 50; // or add some value?
    stack->data = (void*)malloc(stack->capacity * sizeof(void*));
}