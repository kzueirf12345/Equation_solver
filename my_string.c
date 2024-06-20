#include "my_string.h"

void string_realloc(string *str, const size_t add_size)
{
    assert(str && "not init string for smart_realloc");

    if (str->data == NULL)
    {
        str->capacity = add_size;
        str->data = (char *)malloc(add_size * sizeof(char));
        str->data[add_size] = '\0';
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