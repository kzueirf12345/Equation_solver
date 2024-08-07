#include "list.h"
#include "render.h"


void destroy_global_objects(void) {
    SDL_FreeSurface(eqin_surface);
    eqin_surface = NULL;
    SDL_FreeSurface(eqin_scroll_surface);
    eqin_scroll_surface = NULL;
}

int main(int argc, char* argv[]) {
    SDL_scc(SDL_Init(SDL_INIT_EVERYTHING));
    TTF_scc(TTF_Init());

    SDL_Window* window = SDL_scp(SDL_CreateWindow(
        "Equations solver",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    ));

    SDL_Renderer* renderer = SDL_scp(SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    ));
    SDL_scc(SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT));

    TTF_Font* font = TTF_scp(TTF_OpenFont("../Montserrat.ttf", 30));

    SDL_StartTextInput();

    SDL_bool quit = SDL_FALSE;
    while (!quit) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                quit = SDL_TRUE;
                break;
            }
            case SDL_TEXTINPUT: {
                const char* syms = event.text.text;
                if (is_good_syms(syms)) {
                    string_realloc(&eqin_text, 1);
                    strcat(eqin_text.data, syms);
                }
                break;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_BACKSPACE && eqin_text.size) {
                    eqin_text.data[--eqin_text.size] = '\0';
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                if (eqin_scroll_rect.w)
                {
                    SDL_Point cursor_pos;
                    SDL_Rect rect = {
                        bg_eqin_scroll_rect.x + eqin_scroll_rect.x + EQIN_HORIZONTAL_PADDING,
                        bg_eqin_scroll_rect.y + EQIN_TOP_PADDING,
                        eqin_scroll_rect.w,
                        eqin_scroll_rect.h
                    };
                    SDL_GetMouseState(&cursor_pos.x, &cursor_pos.y);
                    if (is_point_in_rect(&cursor_pos, &rect)) {
                        is_movable_eqin_scroll = SDL_TRUE;
                        // printf("down\n");
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                is_movable_eqin_scroll = SDL_FALSE;
                // printf("up\n");
                break;
            }
            case SDL_MOUSEMOTION: {
                if (is_movable_eqin_scroll)
                {
                    eqin_scroll_rect.x += event.motion.xrel;
                    eqin_scroll_rect.x = MIN(EQIN_WIDTH - 2*EQIN_SCROLL_HORIZONTAL_PADDING- eqin_scroll_rect.w,
                                         MAX(0, eqin_scroll_rect.x));
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

    destroy_global_objects();

    free(eqin_text.data);
    eqin_text.data = NULL;
    SDL_StopTextInput();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    TTF_CloseFont(font);
    font = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;
}