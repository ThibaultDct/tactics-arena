#ifndef graphics_h
#define graphics_h

#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "audio.h"
#include "struct.h"

SDL_Surface * loadImage(const char * img);
SDL_Texture * loadTexture(SDL_Renderer * renderer, SDL_Surface * surface);
void displayText(SDL_Renderer *renderer, int x, int y, int size, char *content, char *text_police, int r, int g, int b);
int displaySprite(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
int closeWindow(SDL_Window *pWindow);
int createGameWindow(int x, int y, Entity * grid);
int displayMenu(int x, int y);

#endif
