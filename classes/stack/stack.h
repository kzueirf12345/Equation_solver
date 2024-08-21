#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include "../my_string/my_string.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct Stack{
    void** data;
    size_t elemsize;
    size_t size;
    size_t capacity;
} Stack;

Stack Stack_create(size_t elemsize, size_t capacity);

void Stack_push(Stack * stack, void* data);

void* Stack_back(Stack* stack);

void Stack_pop(Stack* stack);

void Stack_print(Stack* stack);

void Stack_clear(Stack* stack, const int capacity);