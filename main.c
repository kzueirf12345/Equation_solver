#include <SDL2/SDL_ttf.h>

#include "list.h"
#include "my_string.h"
#include "errors.h"

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

int main(int argc, char *argv[])
{
    SDL_scc(SDL_Init(SDL_INIT_EVERYTHING));
    TTF_scc(TTF_Init());

    SDL_Window *window = SDL_scp(SDL_CreateWindow(
        "Equations solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN));

    SDL_Renderer *renderer = SDL_scp(SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    SDL_scc(SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT));

    TTF_Font *font = TTF_scp(TTF_OpenFont("../Montserrat.ttf", 24));

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
                const char *syms = event.text.text;
                if (is_good_syms(syms))
                {
                    string_realloc(&text, 1);
                    strcat(text.data, syms);
                }
                break;
            }
            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_BACKSPACE && text.size)
                {
                    text.data[--text.size] = '\0';
                }
                break;
            }
            }
        }
        SDL_Rect textbox_rect = {50, 100, SCREEN_WIDTH - 100, 200};

        SDL_scc(SDL_SetRenderDrawColor(renderer, PARSE_COLOR(SCREEN_COLOR)));
        SDL_scc(SDL_RenderClear(renderer));

        SDL_Surface *textbox_surface =
            SDL_scp(SDL_CreateRGBSurface(0, textbox_rect.w, textbox_rect.h, 8, 0, 0, 0, 0));
        SDL_Texture *textbox_texture = SDL_scp(SDL_CreateTextureFromSurface(renderer, textbox_surface));
        SDL_RenderCopy(renderer, textbox_texture, NULL, &textbox_rect);

        if (text.size)
        {
            SDL_Color color = {100, 100, 100, 255};
            textbox_surface = TTF_scp(TTF_RenderText_Solid(font, text.data, color));
            textbox_texture = SDL_scp(SDL_CreateTextureFromSurface(renderer, textbox_surface));

            textbox_rect.x += 10;
            textbox_rect.y += 20;
            textbox_rect.w = textbox_surface->w;
            textbox_rect.h = textbox_surface->h;

            SDL_scc(SDL_RenderCopy(renderer, textbox_texture, NULL, &textbox_rect));
        }

        SDL_FreeSurface(textbox_surface);
        SDL_DestroyTexture(textbox_texture);
        textbox_surface = NULL;
        textbox_texture = NULL;

        SDL_RenderPresent(renderer);
    }

    free(text.data);
    SDL_StopTextInput();
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);

    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;
}