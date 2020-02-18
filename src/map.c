#include <stdio.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"
#include "graphics.h"
#include "struct.h"
#include "audio.h"

SDL_Texture *tile = NULL,
			*s_tile = NULL,
			*pers = NULL,
			*mountain = NULL;

void loadMapTextures(SDL_Renderer * renderer)
// Load all the map related textures
{
	if (tile != NULL) 		SDL_DestroyTexture(tile), 		tile = NULL;
	if (s_tile != NULL) 	SDL_DestroyTexture(s_tile), 	s_tile = NULL;
	if (pers != NULL) 		SDL_DestroyTexture(pers), 		pers = NULL;
	if (mountain != NULL) 	SDL_DestroyTexture(mountain), 	mountain = NULL;

	// Loading non-selected tile texture
	tile = loadTexture(renderer, loadImage("../inc/img/tile_64.png"));

	// Loading selected tile texture
	s_tile = loadTexture(renderer, loadImage("../inc/img/tile_selected_64.png"));

	// Loading character sprite
	pers = loadTexture(renderer, loadImage("../inc/sprites/Model/Sprite_sheets/Sprite_sheet_base/Sprite_model.png"));

	// Loading mountain sprite
	mountain = loadTexture(renderer, loadImage("../inc/img/mountain_64.png"));
}

int setSelected(SDL_Renderer *renderer, int x, int y, int xpos, int ypos)
// Set the tile selected
{
	SDL_Rect imgDestRect;

	imgDestRect.x = x*64+xpos;
  	imgDestRect.y = y*64+ypos;
	SDL_QueryTexture(s_tile, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
	SDL_RenderCopy(renderer, s_tile, NULL, &imgDestRect);
	
	SDL_RenderPresent(renderer);

	return 1;
}

int displayMap(SDL_Renderer *renderer, int x, int y, Entity * grid)
// Display the map
{
    SDL_Rect imgDestRect;

	loadMapTextures(renderer);

    for (int i=0; i < 10; i++){
        for (int j=0; j < 10; j++){

			imgDestRect.x = x+j*64;
			imgDestRect.y = y+i*64;
			SDL_QueryTexture(tile, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
			SDL_RenderCopy(renderer, tile, NULL, &imgDestRect);

			if ((*(grid+i*10+j)).cha_id == 1){
				displaySprite(renderer, mountain, x+j*64, y+i*64);
			} else if ((*(grid+i*10+j)).cha_id == 2){
				displaySprite(renderer, pers, x+j*64-25, y+i*64-38);
			}
        }
    }
	
	return 1;
}
