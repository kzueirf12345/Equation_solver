#include "my_string.h"

void string_realloc(string *str, size_t add_size)
{
    assert(str && "not init string for smart_realloc");

    if (str->data == NULL)
    {
        str->capacity = add_size;
        str->data = (char *)malloc(add_size * sizeof(char));
        str->data[0] = '\0';
    }
    else if (str->size + add_size >= str->capacity)
    {
        str->capacity = MAX(2 * str->capacity, add_size + str->size);
        str->data = (char *)realloc(str->data, str->capacity * sizeof(char));
    }
    str->size += add_size;
    return;
}

void string_swap(char **str1_ptr, char **str2_ptr)
{
    char *temp = *str1_ptr;
    *str1_ptr = *str2_ptr;
    *str2_ptr = temp;
}

SDL_bool is_good_sym(char sym)
{
    return (SDL_bool)('a' <= sym && sym <= 'z' || 'A' <= sym && sym <= 'Z' ||
    '0' <= sym && sym <= '9' ||
    sym == '*' || sym == '+' || sym == '-' || sym == '/' || sym == '^' || sym == '=' ||
    sym == '.' || sym == ',');
}

SDL_bool is_good_syms(const char* syms)
{
    for (size_t i = 0; syms[i] != '\0'; ++i)
    {
        if (!is_good_sym(syms[i]))
        {
            return SDL_FALSE;
        }
    }
    return SDL_TRUE;
}
