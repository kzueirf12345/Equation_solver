#include "render.h"

SDL_bool is_point_in_rect(SDL_Point *point, SDL_Rect *rect) {
    return (rect->x <= point->x) && (point->x <= rect->x + rect->w) && (rect->y <= point->y) &&
           (point->y <= rect->y + rect->h);
}

void balance_eqin_scroll_width() {
    offset_eqin_scroll = MIN(BG_EQIN_SCROLL_WIDTH - eqin_scroll_rect.w, MAX(0, offset_eqin_scroll));
    eqin_scroll_rect.x = EQIN_SCROLL_HORIZONTAL_PADDING + offset_eqin_scroll;
}

void blit_eqin_text(TTF_Font *font, int *const text_size) {
    if (!eqin_text.size) {
        return;
    }
    SDL_Surface *eqin_text_surface =
        SDL_scp(TTF_RenderText_Blended_Wrapped(font, eqin_text.data, FONT_COLOR, 0));

    *text_size = eqin_text_surface->w;

    SDL_Rect eqin_text_rect = {(eqin_scroll_rect.w != BG_EQIN_SCROLL_WIDTH
                                    ? (offset_eqin_scroll * BG_EQIN_TEXT_WIDTH / eqin_scroll_rect.w)
                                    : offset_eqin_scroll),
                               0, MIN(eqin_text_surface->w, BG_EQIN_TEXT_WIDTH),
                               eqin_text_surface->h};

    SDL_Rect bg_eqin_text_rect = {EQIN_TEXT_HORIZONTAL_PADDING,
                                  (eqin_surface->h - eqin_text_surface->h - EQIN_SCROLL_HEIGHT -
                                   2 * EQIN_SCROLL_VERTICAL_PADDING) /
                                      2,
                                  eqin_surface->w, eqin_surface->h};

    SDL_scc(SDL_BlitSurface(eqin_text_surface, &eqin_text_rect, eqin_surface, &bg_eqin_text_rect));

    SDL_FreeSurface(eqin_text_surface);
    eqin_text_surface = NULL;
}

void blit_eqin_scroll(int text_size) {
    if (text_size <= BG_EQIN_TEXT_WIDTH || !text_size) {
        eqin_scroll_rect.w = BG_EQIN_SCROLL_WIDTH;
        offset_eqin_scroll = 0;
        return;
    }
    eqin_scroll_rect.w = (BG_EQIN_TEXT_WIDTH * BG_EQIN_TEXT_WIDTH) / text_size;

    eqin_scroll_surface =
        SDL_scp(SDL_CreateRGBSurface(0, eqin_scroll_rect.w, eqin_scroll_rect.h, 32, 0, 0, 0, 0));

    SDL_scc(SDL_FillRect(eqin_scroll_surface, NULL,
                         SDL_ColorToUint32(SCROLL_COLOR, eqin_scroll_surface->format)));

    SDL_scc(SDL_BlitSurface(eqin_scroll_surface, NULL, eqin_surface, &eqin_scroll_rect));

    SDL_FreeSurface(eqin_scroll_surface);
    eqin_scroll_surface = NULL;
    // printf("eqin_scroll_rect: %d, %d, %d, %d\n", eqin_scroll_rect.x, eqin_scroll_rect.y,
    //        eqin_scroll_rect.w, eqin_scroll_rect.h);
}

void render_eqin(SDL_Renderer *renderer, TTF_Font *font) {
    eqin_surface = SDL_scp(SDL_CreateRGBSurface(0, eqin_rect.w, eqin_rect.h, 32, 0, 0, 0, 0));
    SDL_scc(
        SDL_FillRect(eqin_surface, NULL, SDL_ColorToUint32(BG_EQIN_COLOR, eqin_surface->format)));

    int text_size = 0;
    balance_eqin_scroll_width();
    blit_eqin_text(font, &text_size);
    blit_eqin_scroll(text_size);

    SDL_Texture *eqin_texture = SDL_scp(SDL_CreateTextureFromSurface(renderer, eqin_surface));
    SDL_FreeSurface(eqin_surface);
    eqin_surface = NULL;

    SDL_scc(SDL_RenderCopy(renderer, eqin_texture, NULL, &eqin_rect));

    SDL_DestroyTexture(eqin_texture);
    eqin_texture = NULL;

    return;
}