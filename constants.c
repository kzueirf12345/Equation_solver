#include "constants.h"

Uint32 SDL_ColorToUint32(SDL_Color color, SDL_PixelFormat* format) {
    return SDL_MapRGBA(format, color.r, color.g, color.b, color.a);
}

const SDL_Color SCREEN_COLOR = {25, 25, 25, 255};
const SDL_Color BG_EQIN_COLOR = {240, 240, 240, 255};
const SDL_Color FONT_COLOR = {100, 100, 100, 255};
const SDL_Color SCROLL_COLOR = {100, 100, 100, 255};



string eqin_text = {NULL, 0, 0};
const SDL_Rect eqin_rect = {EQIN_HORIZONTAL_PADDING, EQIN_TOP_PADDING, EQIN_WIDTH, EQIN_HEIGHT};
SDL_Surface* eqin_surface = NULL;

SDL_Rect bg_eqin_scroll_rect = {
    EQIN_SCROLL_HORIZONTAL_PADDING, 
    EQIN_HEIGHT - 2*EQIN_SCROLL_VERTICAL_PADDING -EQIN_SCROLL_HEIGHT, 
    EQIN_WIDTH - 2*EQIN_SCROLL_HORIZONTAL_PADDING, 
    EQIN_SCROLL_HEIGHT
};
SDL_Surface* eqin_scroll_surface = NULL;



SDL_bool is_movable_eqin_scroll = SDL_FALSE;
SDL_Rect eqin_scroll_rect = {
    0, //offset
    0,
    0,
    EQIN_SCROLL_HEIGHT
};
