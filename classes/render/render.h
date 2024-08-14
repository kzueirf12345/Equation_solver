#pragma once

#include <SDL2/SDL.h>
#if __APPLE__
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include "../constants/constants.h"

SDL_bool is_point_in_rect(SDL_Point* point, SDL_Rect* rect);
void balance_eqin_scroll_width();

void blit_eqin_text(TTF_Font* font, int* const text_size);
void blit_eqin_scroll(int text_size);
void render_eqin(SDL_Renderer* renderer, TTF_Font* font);
