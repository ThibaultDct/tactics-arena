#ifndef map_h
#define map_h

#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "audio.h"
#include "struct.h"

int displayMap(SDL_Renderer *renderer, int x, int y);
int setSelected(SDL_Renderer *renderer, int x, int y);

#endif