#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include "errors.h"
#include "my_string.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


// EQIN size
#define EQIN_HEIGHT 150
#define EQIN_HORIZONTAL_PADDING 50
#define EQIN_WIDTH (SCREEN_WIDTH-2*EQIN_HORIZONTAL_PADDING)
#define EQIN_TOP_PADDING 100

#define EQIN_SCROLL_HEIGHT 20
#define EQIN_SCROLL_VERTICAL_PADDING 5
#define EQIN_SCROLL_HORIZONTAL_PADDING 30

#define EQIN_TEXT_HORIZONTAL_PADDING (EQIN_SCROLL_HORIZONTAL_PADDING)
#define BG_EQIN_TEXT_WIDTH ((EQIN_WIDTH) - (2*(EQIN_TEXT_HORIZONTAL_PADDING)))

#define PARSE_COLOR(color) color.r, color.g, color.b, color.a

Uint32 SDL_ColorToUint32(SDL_Color color, SDL_PixelFormat* format);

extern const SDL_Color SCREEN_COLOR;
extern const SDL_Color BG_EQIN_COLOR;
extern const SDL_Color FONT_COLOR;
extern const SDL_Color SCROLL_COLOR;


extern string eqin_text;
extern const SDL_Rect eqin_rect;
extern SDL_Surface* eqin_surface;

extern SDL_Rect bg_eqin_scroll_rect;
extern SDL_Surface* eqin_scroll_surface;


extern int offset_eqin_scroll;
extern SDL_bool is_movable_eqin_scroll;
extern SDL_Rect eqin_scroll_rect;

