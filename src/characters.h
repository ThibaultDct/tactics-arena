#ifndef characters_h
#define characters_h

#include "struct.h"
#include "common.h"

int displayCharacters(SDL_Renderer * renderer, Tile * grid, int x, int y);
int setEntityToTile(Tile * grid, Entity * entity, Coord tile, int xSize, int ySize);
int displayCharacters(SDL_Renderer * renderer, Tile * grid, int x, int y);

#endif