#ifndef characters_h
#define characters_h

#include "struct.h"

int loadSprites(SDL_Renderer * renderer, TabTexture * cSprites);
int setEntityToTile(Tile * grid, Entity * entity, Coord tile, int xSize, int ySize);
int displayCharacters(SDL_Renderer * renderer, TabTexture * cSprites, Tile * grid, int x, int y);

#endif