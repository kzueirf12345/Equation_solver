#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "constants.h"
#include "errors.h"
#include "my_string.h"

SDL_bool is_point_in_rect(SDL_Point* point, SDL_Rect* rect);

void blit_eqin_text(TTF_Font* font, int* const text_size);
void blit_eqin_scroll(int text_size);
void render_eqin(SDL_Renderer* renderer, TTF_Font* font);
