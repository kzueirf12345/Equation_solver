#include "my_string.h"
#include <assert.h>
#include <string.h>

void* recalloc(void* dest, size_t old_size, size_t new_size)
{
    void* result = calloc(new_size, 1);
    if (!result)
        return 0;
    memcpy(result, dest, old_size);
    free(dest);
    return result;
}

String String_create(const char* const data, size_t size)
{
    String str = { (char*)calloc((size + 1), sizeof(char)), size + 1, size };
    memcpy(str.data, data, size);
    return str;
}

void String_copy(String* const dest, const String* const str)
{
    assert(dest == NULL && "can't copy to NULL");
    dest->size = str->size;
    dest->capacity = dest->capacity;
    memcpy(dest->data, str->data, str->size);
}

void String_realloc(String* str, size_t add_size)
{
    assert(str && "not init String");

    if (str->data == NULL) {
        *str = String_create(NULL, add_size);
        return;
    }
    if (str->size + add_size >= str->capacity) {
        str->capacity = MAX(2 * str->capacity, str->size + add_size + 1);
        str->data = (char*)recalloc(str->data, str->size, str->capacity);
    }
    str->size += add_size;
}

void String_swap(char** str1_ptr, char** str2_ptr)
{
    char* temp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = temp;
}

void String_push_back_str(String* dest, String* source)
{
    String_realloc(dest, source->size);
    strcat(dest->data, source->data);
}

void String_push_back_char(String* dest, char chr)
{
    String_realloc(dest, 1);
    dest->data[dest->size - 1] = chr;
}

char String_back(const String* const str)
{
    assert((str && str->data) && "not init String");
    assert(str->size && "String is empty");
    return str->data[str->size - 1];
}

char String_pop_back(String* str)
{
    char pop_char = String_back(str);
    str->data[--str->size] = '\0';
    return pop_char;
}

SDL_bool is_good_sym(char sym)
{
    return (SDL_bool)('a' <= sym && sym <= 'z' || 'A' <= sym && sym <= 'Z' || '0' <= sym && sym <= '9' || sym == '*' || sym == '+' || sym == '-' || sym == '/' || sym == '^' || sym == '=' || sym == '.' || sym == ',' || sym == ' ');
}

SDL_bool is_good_syms(const char* syms)
{
    for (size_t i = 0; syms[i] != '\0'; ++i) {
        if (!is_good_sym(syms[i])) {
            return SDL_FALSE;
        }
    }
    return SDL_TRUE;
}

int String_to_int(const String* str)
{
    assert(str && "String not initialized");
    return atoi(str->data);
}

String String_char_to_string(const char sym)
{
    char tmp[2];
    tmp[0] = sym;
    tmp[1] = '\0';
    return String_create(tmp, 1);
}

void String_clear(String* const str)
{
    for (int i = 0; i < str->capacity; ++i) {
        str->data[i] = '\0';
    }
    str->size = 0;
}