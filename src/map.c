#include <stdio.h>
#include <math.h>
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

	printf("[GRAPHICS] Chargement des textures du jeu...\n");

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

int selectTile(Entity * grid, int xpos, int ypos, int mx, int my, int pxBase)
// Set the tile selected according to 2D iso
{
	int xIndex, yIndex, xIsoOrigin, yIsoOrigin;

	for (int i=0; i<30; i++){
		for (int j=0; j<10; j++){
			(*(grid+i*10+j)).selected = 0;
		}
	}

	xIsoOrigin = xpos;
	yIsoOrigin = ypos+10*(pxBase/4);

	xIndex = floor(((my-yIsoOrigin)/(pxBase/2) + ((mx-xIsoOrigin)/pxBase)))-1;
	yIndex = ceil((((mx-xIsoOrigin)/pxBase) - (my-yIsoOrigin)/(pxBase/2)))-1;

	if (xIndex > 29 || yIndex > 9 || xIndex < 0 || yIndex < 0) return 0;

	printf("[GRAPHICS] Case sélectionnée : %d, %d\n", xIndex, yIndex);
	(*(grid+xIndex*10+yIndex)).selected = 1;

	return 1;
}

int displayMap(SDL_Renderer *renderer, int x, int y, int pxBase, Entity * grid)
// Display the map
{
    SDL_Rect imgDestRect;

	SDL_Texture *block = NULL,
				*s_block = NULL;

	if (pxBase == 64){
		block = tile;
		s_block = sb_tile;
	} else {
		block = tile_big;
		s_block = sb_big_tile;
	}

	/* Le fond de la fenêtre sera blanc */
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
	SDL_RenderClear(renderer);

    for (int i=0; i < 30; i++){
        for (int j=9; j >= 0; j--){
			if ((*(grid+i*10+j)).cha_id != 0){

				imgDestRect.x = x+(j+1)*(pxBase/2)+(i+1)*(pxBase/2);
				imgDestRect.y = y+i*(pxBase/4)+(10-j)*(pxBase/4);

				if ((*(grid+i*10+j)).selected){
					SDL_QueryTexture(s_block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
					SDL_RenderCopy(renderer, s_block, NULL, &imgDestRect);
				} else {
					SDL_QueryTexture(block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
					SDL_RenderCopy(renderer, block, NULL, &imgDestRect);
				}

				char pos[6];
				sprintf(pos, "%d,%d", i, j);
				displayText(renderer, x+(j+1)*(pxBase/2)+(i+1)*(pxBase/2)+(pxBase/2)-10, y+i*(pxBase/4)+(10-j)*(pxBase/4)+(pxBase/4), (pxBase/64)*10, pos, "../inc/font/Pixels.ttf", 255, 50, 50);

			}
        }
    }

	char str[12];
	sprintf(str, "%d, %d", x, y);

	displayText(renderer, 20, 20, 20, str, "../inc/font/Pixels.ttf", 255, 255, 255);
	
	SDL_RenderPresent(renderer);

	return 1;
}
