#pragma once

#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h> long time deprecated. everything is in stdlib.h now

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void* recalloc(void* dest, size_t old_size, size_t new_size);

typedef struct string {
    char* data;
    size_t capacity;
    size_t size;
} string;

string screate(const char* const data, size_t size);
void scopy(string* const dest, const string* const str);
void srealloc(string* str, size_t add_size);
void sswap(char** str1_ptr, char** str2_ptr);

void spush_back_str(string* dest, string* source);
void spush_back_char(string* dest, char chr);
char sback(const string* const str);
char spop_back(string* const str);
int stoi(const string* const str);
string sctos(const char sym); // char to string
void sclear(string* const str);

SDL_bool is_good_sym(char sym);
SDL_bool is_good_syms(const char* syms);