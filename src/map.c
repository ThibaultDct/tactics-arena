#include <stdio.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"
#include "graphics.h"
#include "struct.h"
#include "audio.h"

SDL_Texture *tile = NULL,
			*sr_tile = NULL,
			*sb_tile = NULL,
			*tile_big = NULL,
			*sr_big_tile = NULL,
			*sb_big_tile = NULL;

void loadMapTextures(SDL_Renderer * renderer)
// Load all the map related textures
{
	if (tile != NULL) 			SDL_DestroyTexture(tile), 			tile = NULL;
	if (sr_tile != NULL) 		SDL_DestroyTexture(sr_tile), 		sr_tile = NULL;
	if (sb_tile != NULL) 		SDL_DestroyTexture(sb_tile), 		sb_tile = NULL;
	if (tile_big != NULL) 		SDL_DestroyTexture(tile_big), 		tile_big = NULL;
	if (sr_big_tile != NULL) 	SDL_DestroyTexture(sr_big_tile), 	sr_big_tile = NULL;
	if (sb_big_tile != NULL) 	SDL_DestroyTexture(sb_big_tile), 	sb_big_tile = NULL;

	// Loading non-selected tile texture (64px)
	tile = loadTexture(renderer, loadImage("../inc/img/block_64.png"));

	// Loading red selected tile texture (64px)
	sr_tile = loadTexture(renderer, loadImage("../inc/img/block_red_64.png"));

	// Loading blue selected tile texture (64px)
	sb_tile = loadTexture(renderer, loadImage("../inc/img/block_blue_64.png"));

	// Loading non-selected tile texture (128px)
	tile_big = loadTexture(renderer, loadImage("../inc/img/block_128.png"));

	// Loading red selected tile texture (128px)
	sr_big_tile = loadTexture(renderer, loadImage("../inc/img/block_red_128.png"));

	// Loading blue selected tile texture (128px)
	sb_big_tile = loadTexture(renderer, loadImage("../inc/img/block_blue_128.png"));
}

int setSelected(SDL_Renderer *renderer, int x, int y, int xpos, int ypos)
// Set the tile selected
{
	SDL_Rect imgDestRect;

	imgDestRect.x = x*64+xpos;
  	imgDestRect.y = y*64+ypos;
	SDL_QueryTexture(sb_tile, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
	SDL_RenderCopy(renderer, sb_tile, NULL, &imgDestRect);
	
	SDL_RenderPresent(renderer);

	return 1;
}

int displayMap(SDL_Renderer *renderer, int x, int y, int pxBase, Entity * grid)
// Display the map
{
    SDL_Rect imgDestRect;

	SDL_Texture *block = NULL;

	if (pxBase == 64) block = tile;
	else block = tile_big;

	/* Le fond de la fenêtre sera blanc */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

    for (int i=0; i < 30; i++){
        for (int j=0; j < 10; j++){
			if ((*(grid+i*10+j)).cha_id != 0){
				if (i%2){
					imgDestRect.x = x+j*pxBase;
					imgDestRect.y = y-((pxBase/4*3)*i)+i*pxBase;
					SDL_QueryTexture(block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
					SDL_RenderCopy(renderer, block, NULL, &imgDestRect);
				} else {
					imgDestRect.x = (x-(pxBase/2))+j*pxBase;
					imgDestRect.y = y-((pxBase/4*3)*i)+i*pxBase;
					SDL_QueryTexture(block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
					SDL_RenderCopy(renderer, block, NULL, &imgDestRect);
				}
			}
        }
    }
	
	SDL_RenderPresent(renderer);

	return 1;
}
