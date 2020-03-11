#include <stdio.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"
#include "graphics.h"
#include "characters.h"

#define _NB_MAX_SPRITES_ 50

TabTexture cSprites[_NB_MAX_SPRITES_];

int loadSprites(SDL_Renderer * renderer, TabTexture * cSprites)
// Load all the textures needed for the characters
{
    int nbSprites = 0;

    freeTextures(cSprites);

    printf("Chargement des textures des personnages...\n");

    nbSprites = addTextureToTable(  cSprites,
                                    loadTexture(renderer, loadImage("../inc/sprites/base/sprite_sheet/64_64/Sprite_frontview_64.png")),
                                    NULL,
                                    "base_model");

    printf("[CHARACTERS] %d texture(s) de personnage(s) chargée(s) !", nbSprites);
    return nbSprites;
}

int setEntityToTile(Tile * grid, Entity * entity, Coord tile, int xSize, int ySize)
// Set an entity to a specific tile
{
    if (tile.x < 0 || tile.x >= xSize || tile.y < 0 || tile.y >= ySize)
    {
        printf("%s\n", error_message[COORD_OUT_OF_BOUND]);
        return COORD_OUT_OF_BOUND;
    };

    if (entity == NULL || grid == NULL)
    {
        printf("%s\n", error_message[POINTER_NULL]);
        return POINTER_NULL;
    }

    (*(grid+tile.x*xSize+tile.y)).entity = entity;
    return OK;
}

int displayCharacters(SDL_Renderer * renderer, Tile * grid, int x, int y)
// Display the characters on the map
{

}