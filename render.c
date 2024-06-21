#include "render.h"

void render_eqin (SDL_Renderer *renderer, TTF_Font* font)
{
    SDL_Rect eqin_rect = {50, 100, SCREEN_WIDTH - 100, 200};
    SDL_Surface *eqin_surface = SDL_scp(SDL_CreateRGBSurface(0, eqin_rect.w, eqin_rect.h, 32, 0, 0, 0, 0));
    SDL_Rect fill_eqin_rect = {0, 0, eqin_rect.w, eqin_rect.h};
    SDL_scc(SDL_FillRect(eqin_surface, &fill_eqin_rect, SDL_MapRGBA(eqin_surface->format, 255, 255, 255, 255)));

    if (eqin_text.size)
    {
        SDL_Surface *text_eqin_surface = TTF_scp(TTF_RenderText_Blended(font, eqin_text.data, FONT_COLOR));
        SDL_scc(SDL_SetSurfaceBlendMode(text_eqin_surface, SDL_BLENDMODE_BLEND));

        SDL_Rect text_eqin_rect = {10, 20, text_eqin_surface->w, text_eqin_surface->h};
        SDL_scc(SDL_BlitSurface(text_eqin_surface, NULL, eqin_surface, &text_eqin_rect));

        SDL_FreeSurface(text_eqin_surface);
        text_eqin_surface = NULL;
    }

    SDL_Texture *eqin_texture = SDL_scp(SDL_CreateTextureFromSurface(renderer, eqin_surface));
    SDL_FreeSurface(eqin_surface);
    eqin_surface = NULL;

    SDL_scc(SDL_RenderCopy(renderer, eqin_texture, NULL, &eqin_rect));
    SDL_DestroyTexture(eqin_texture);
    eqin_texture = NULL;
    return;
}