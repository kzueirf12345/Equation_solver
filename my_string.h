#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct string
{
    char *data;
    size_t capacity;
    size_t size;
} string;

void string_realloc(string *str, const size_t add_size);

void string_swap(char **str1_ptr, char **str2_ptr);