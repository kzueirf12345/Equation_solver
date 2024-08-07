#pragma once

#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct string {
    char *data;
    size_t capacity;
    size_t size;
} string;

void string_realloc(string *str, size_t add_size);
void string_swap(char **str1_ptr, char **str2_ptr);

SDL_bool is_good_sym(char sym);
SDL_bool is_good_syms(const char *syms);