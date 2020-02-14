#ifndef graphics_h
#define graphics_h

#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "audio.h"

void loadMenuTextures(SDL_Renderer *renderer);
void freeTextures(void);
void displayText(SDL_Renderer *renderer, TTF_Font *police, int x, int y, int size, char *content, char *text_police, int r, int g, int b);
//int displaySprite(SDL_Renderer *renderer, char *sprite, int x, int y);
int displaySprite(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
int closeWindow(SDL_Window *pWindow);
int createGameWindow(int x, int y);
int displayMenu(int x, int y);

#endif
