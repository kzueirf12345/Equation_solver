#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "list.h"
#include "my_string.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BOARD_WIDTH 100
#define BOARD_HEIGHT 100

typedef struct
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;
#define PARSE_COLOR(color) color.r, color.g, color.b, color.a

const Color SCREEN_COLOR = {25, 25, 25, 255};
const Color TEXTBOX_COLOR = {100, 0, 0, 255};

string text = {NULL, 0, 0};

int scc(int code)
{
    if (code < 0)
    {
        printf("SDL error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return code;
}
void *scp(void *ptr)
{
    if (ptr == NULL)
    {
        printf("SDL error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void render_game(SDL_Renderer *renderer)
{
    SDL_Color color = {10, 10, 10, 255};
    SDL_Surface *surface =
        scp(SDL_CreateRGBSurface(0, 100, 100, 8, 0, 0, 0, 0));
    SDL_Texture *texture = scp(SDL_CreateTextureFromSurface(renderer, surface));
    SDL_FreeSurface(surface);
    SDL_Rect rect = {100, 100, 100, 100};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

int main(int argc, char *argv[])
{
    scc(SDL_Init(SDL_INIT_EVERYTHING));

    SDL_Window *window = scp(SDL_CreateWindow(
        "Equations solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN));

    SDL_Renderer *renderer = scp(SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

    scc(SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT));

    SDL_StartTextInput();

    SDL_bool quit = SDL_FALSE;
    while (!quit)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
            {
                quit = SDL_TRUE;
                break;
            }
            case SDL_TEXTINPUT:
            {
                string_realloc(&text, strlen(event.text.text));
                strcat(text.data, event.text.text);
                // printf("%s\n %d %d\n", text.data, (int)text.size, (int)text.capacity);
                break;
            }
            }
        }

        scc(SDL_SetRenderDrawColor(renderer, PARSE_COLOR(SCREEN_COLOR)));
        scc(SDL_RenderClear(renderer));

        render_game(renderer);

        SDL_RenderPresent(renderer);
    }

    free(text.data);
    SDL_StopTextInput();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}