#ifndef map_editor_h
#define map_editor_h

#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "audio.h"
#include "struct.h"

void loadEditorTextures(SDL_Renderer * renderer);
int displayEditorMap(SDL_Renderer *renderer, int x, int y, int pxBase, Tile * grid, int xSize, int ySize, int select, int xWinSize, int yWinSize);
int createMapEditorWindow(int x, int y, Tile * grid, int xSize, int ySize);

#endif
