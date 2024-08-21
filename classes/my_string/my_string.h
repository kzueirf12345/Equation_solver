#pragma once

#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h> long time deprecated. everything is in stdlib.h now

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void* recalloc(void* dest, size_t old_size, size_t new_size);

typedef struct String {
    char* data;
    size_t capacity;
    size_t size;
} String;

String String_create(const char* const data, size_t size);
void String_copy(String* const dest, const String* const str);
void String_realloc(String* str, size_t add_size);
void String_swap(char** str1_ptr, char** str2_ptr);

void String_push_back_str(String* dest, String* source);
void String_push_back_char(String* dest, char chr);
char String_back(const String* const str);
char String_pop_back(String* const str);
int String_to_int(const String* const str);
String String_char_to_string(const char sym); // char to String
void String_clear(String* const str);