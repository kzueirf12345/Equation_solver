#include "my_string.h"

void *recalloc(void *dest, size_t old_size, size_t new_size) {
    void *result = calloc(new_size, 1);
    if (!result) return 0;
    memcpy(result, dest, old_size);
    free(dest);
    return result;
}

string create_string(const char *const data, size_t size) {
    string str = {(char *)calloc((size + 1), sizeof(char)), size + 1, size};
    memcpy(str.data, data, size);
    return str;
}

void srealloc(string *str, size_t add_size) {
    assert(str && "not init string");

    if (str->data == NULL) {
        *str = create_string(NULL, add_size);
        return;
    }
    if (str->size + add_size >= str->capacity) {
        str->capacity = MAX(2 * str->capacity, str->size + add_size + 1);
        str->data = (char *)recalloc(str->data, str->size, str->capacity);
    }
    str->size += add_size;
}

void sswap(char **str1_ptr, char **str2_ptr) {
    char *temp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = temp;
}

void spush_back_str(string *dest, string *source) {
    srealloc(dest, source->size);
    strcat(dest->data, source->data);
}

void spush_back_char(string *dest, char chr) {
    srealloc(dest, 1);
    dest->data[dest->size - 1] = chr;
}

char sback(string *const str) { 
    assert((str && str->data) && "not init string");
    assert(str->size && "string is empty");
    return str->data[str->size-1];
}

char spop_back(string *str) { 
    char pop_char = sback(str);
    str->data[--str->size] = '\0';
    return pop_char;
}

SDL_bool is_good_sym(char sym) {
    return (SDL_bool)('a' <= sym && sym <= 'z' || 'A' <= sym && sym <= 'Z' ||
                      '0' <= sym && sym <= '9' || sym == '*' || sym == '+' || sym == '-' ||
                      sym == '/' || sym == '^' || sym == '=' || sym == '.' || sym == ',' ||
                      sym == ' ');
}

SDL_bool is_good_syms(const char *syms) {
    for (size_t i = 0; syms[i] != '\0'; ++i) {
        if (!is_good_sym(syms[i])) {
            return SDL_FALSE;
        }
    }
    return SDL_TRUE;
}
