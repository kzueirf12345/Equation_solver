#pragma once

#include <SDL2/SDL.h>
#if __APPLE__
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif
#include <stdio.h>
#include <stdlib.h>

int SDL_scc(int code);
void *SDL_scp(void *ptr);

int TTF_scc(int code);
void *TTF_scp(void *ptr);