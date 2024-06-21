#pragma once

#include <stdio.h>
#include "my_string.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BOARD_WIDTH 100
#define BOARD_HEIGHT 100

#define PARSE_COLOR(color) color.r, color.g, color.b, color.a

extern const SDL_Color SCREEN_COLOR;
extern const SDL_Color BG_EQIN_COLOR;
extern const SDL_Color FONT_COLOR;
extern string eqin_text;
