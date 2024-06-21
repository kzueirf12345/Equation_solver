#include "list.h"
#include "render.h"

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

    TTF_Font* font = TTF_scp(TTF_OpenFont("../Montserrat.ttf", 24));

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
                    string_realloc(&eqin_text, 1);
                    strcat(eqin_text.data, syms);
                }
                break;
            }
            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_BACKSPACE && eqin_text.size)
                {
                    eqin_text.data[--eqin_text.size] = '\0';
                }
                break;
            }
            }
        }

        SDL_scc(SDL_SetRenderDrawColor(renderer, PARSE_COLOR(SCREEN_COLOR)));
        SDL_scc(SDL_RenderClear(renderer));

        render_eqin(renderer, font);

        SDL_RenderPresent(renderer);
    }

    free(eqin_text.data);
    eqin_text.data = NULL;
    SDL_StopTextInput();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    TTF_CloseFont(font);
    font = NULL;

    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;
}