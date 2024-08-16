#include "classes/polynom/polynom.h"
#include "classes/render/render.h"
#include "classes/stack/stack.h"

#define DEBUG

int main(int argc, char* argv[]) {
#ifdef DEBUG
    // // CHECK ONE
    // List list = create_List(NULL, NULL, 0);
    // push_back(&list, create_Data(1, 6));
    // push_back(&list, create_Data(1, 6));
    // push_back(&list, create_Data(1, 6));
    // push_back(&list, create_Data(1, 2));
    // push_back(&list, create_Data(10, 5));
    // push_back(&list, create_Data(1, 6));
    // push_back(&list, create_Data(1, 100));
    // push_back(&list, create_Data(228, 5));
    // push_back(&list, create_Data(666, 0));
    // push_back(&list, create_Data(1337, 1));
    // push_back(&list, create_Data(52, 0));
    // push_back(&list, create_Data(52, 0));
    // print_polynom(&list, "base list");
    // list = msort(&list);
    // print_polynom(&list, "sorted list");
    // reduct_sorted_polynom(&list);
    // print_polynom(&list, "reducted list");

    // //CHECK TWO
    // printf("old list: \t");
    // for (size_t i = 1; i <= 25; ++i)
    // {
    //     const int num = rand()%1000;
    //     push_back(&list, create_Data(0, num));
    //     printf("%d ", num);
    // }
    // list = msort(&list);
    // printf("\nnew list: \t");
    // for (Node* it = list.left; it != NULL; it = it->next)
    // {
    //     printf("%d ", it->data.power);
    // }
    // printf("\n");

    // //CHECK THREE
    // token = 9x
    // token -> node
    // node -> list
    // 9x 8x 4 - 6x 2 + * +
    // string tmp = screate("9x+(8x-4)*(6x+2)", 16);
    // printf("%s\n", pol_nat(&tmp).data);

    // // CHECK FOUR
    // Stack stack = Stack_create(sizeof(int), 5);
    // for (int i = 0; i < 30; ++i) {
    //     Stack_push(&stack, &i);
    // }
    // Stack_print(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_print(&stack);
    // for (int i = 0; i < 10; ++i) {
    //     Stack_push(&stack, &i);
    // }
    // Stack_print(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_pop(&stack);
    // Stack_print(&stack);
    // free(stack.data);
    // stack.data = 0;

#else
    SDL_scc(SDL_Init(SDL_INIT_EVERYTHING));
    TTF_scc(TTF_Init());

    SDL_Window* window = SDL_scp(
        SDL_CreateWindow("Equations solver", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS));

    SDL_Renderer* renderer = SDL_scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    SDL_scc(SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT));

    TTF_Font* font = TTF_scp(TTF_OpenFont("../Montserrat.ttf", 30));

    SDL_StartTextInput();
    eqin_text = screate(NULL, 0);

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
                        spush_back_char(&eqin_text, syms[0]);
                    }
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_BACKSPACE && eqin_text.size) {
                        spop_back(&eqin_text);
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (eqin_scroll_rect.w < BG_EQIN_SCROLL_WIDTH) {
                        SDL_Point cursor_pos;
                        SDL_Rect rect = {eqin_scroll_rect.x + EQIN_HORIZONTAL_PADDING,
                                         eqin_scroll_rect.y + EQIN_TOP_PADDING, eqin_scroll_rect.w,
                                         eqin_scroll_rect.h};
                        SDL_scc(SDL_GetMouseState(&cursor_pos.x, &cursor_pos.y));
                        if (is_point_in_rect(&cursor_pos, &rect)) {
                            is_movable_eqin_scroll = SDL_TRUE;
                        }
                    }
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    is_movable_eqin_scroll = SDL_FALSE;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    if (is_movable_eqin_scroll) {
                        offset_eqin_scroll += event.motion.xrel;
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
    TTF_CloseFont(font);
    font = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;

#endif
}