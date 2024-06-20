#include "errors.h"

int SDL_scc(int code)
{
    if (code < 0)
    {
        printf("SDL error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return code;
}
void *SDL_scp(void *ptr)
{
    if (ptr == NULL)
    {
        printf("SDL error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return ptr;
}

int TTF_scc(int code)
{
    if (code < 0)
    {
        printf("TTF error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    return code;
}
void *TTF_scp(void *ptr)
{
    if (ptr == NULL)
    {
        printf("TTF error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    return ptr;
}