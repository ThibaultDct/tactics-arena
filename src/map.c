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
			*water_tile = NULL,
			*tile_big = NULL,
			*sr_big_tile = NULL,
			*sb_big_tile = NULL,
			*water_big_tile = NULL;

void loadMapTextures(SDL_Renderer * renderer)
// Load all the map related textures
{
	if (tile != NULL) 			SDL_DestroyTexture(tile), 			tile = NULL;
	if (sr_tile != NULL) 		SDL_DestroyTexture(sr_tile), 		sr_tile = NULL;
	if (sb_tile != NULL) 		SDL_DestroyTexture(sb_tile), 		sb_tile = NULL;
	if (water_tile != NULL) 	SDL_DestroyTexture(water_tile), 	water_tile = NULL;
	if (tile_big != NULL) 		SDL_DestroyTexture(tile_big), 		tile_big = NULL;
	if (sr_big_tile != NULL) 	SDL_DestroyTexture(sr_big_tile), 	sr_big_tile = NULL;
	if (sb_big_tile != NULL) 	SDL_DestroyTexture(sb_big_tile), 	sb_big_tile = NULL;
	if (water_big_tile != NULL) SDL_DestroyTexture(water_big_tile), water_big_tile = NULL;

	printf("[GRAPHICS] Chargement des textures du jeu...\n");

	// Loading non-selected tile texture (64px)
	tile = loadTexture(renderer, loadImage("../inc/img/block_64.png"));

	// Loading red selected tile texture (64px)
	sr_tile = loadTexture(renderer, loadImage("../inc/img/block_red_64.png"));

	// Loading blue selected tile texture (64px)
	sb_tile = loadTexture(renderer, loadImage("../inc/img/block_blue_64.png"));

	// Loading water block texture (64px)
	water_tile = loadTexture(renderer, loadImage("../inc/img/water_64.png"));

	// Loading non-selected tile texture (128px)
	tile_big = loadTexture(renderer, loadImage("../inc/img/block_128.png"));

	// Loading red selected tile texture (128px)
	sr_big_tile = loadTexture(renderer, loadImage("../inc/img/block_red_128.png"));

	// Loading blue selected tile texture (128px)
	sb_big_tile = loadTexture(renderer, loadImage("../inc/img/block_blue_128.png"));

	// Loadding water block texture (128px)
	water_big_tile = loadTexture(renderer, loadImage("../inc/img/water_128.png"));
}

float crossProduct(Vector AB, Vector AC)
// Renvoie le produit vectoriel
{
	return (( AB.y * AC.x ) - ( AB.x * AC.y ));
}

int selectTile(Tile * grid, int xpos, int ypos, int mx, int my, int pxBase, int xSize, int ySize)
// Set the tile selected according to 2D iso from 2D coordinates
{
	int xIndex, yIndex, xIsoOrigin, yIsoOrigin, xTile, yTile;
	float cpAB, cpBC, cpDC, cpAD;

	// On déselectionne toutes les cases
	for (int i=0; i<xSize; i++){
		for (int j=0; j<ySize; j++){
			(*(grid+i*xSize+j)).selected = 0;
		}
	}

	// Position de l'origine de la map en 2D isométrique
	xIsoOrigin = xpos;
	yIsoOrigin = ypos+ySize*(pxBase/4);

	// Coordonnées 2D -> 2D iso
	xIndex = floor(((my-yIsoOrigin)/(pxBase/2) + ((mx-xIsoOrigin)/pxBase)))-1;
	yIndex = ceil((((mx-xIsoOrigin)/pxBase) - (my-yIsoOrigin)/(pxBase/2)))-1;

	if (my < yIsoOrigin){
		xIndex--;
		yIndex++;
	}

	xTile = xpos+((((xIndex+yIndex)/2)+1)*pxBase);
	yTile = ypos+((ySize-(yIndex-xIndex))*(pxBase/4)+(pxBase/4));
	printf("xTile : %d yTile : %d\n", xTile, yTile);

	// Calcul des coordonnées des 4 coins de la tile
	Coord A = { xTile, yTile };
	Coord B = { xTile + (pxBase / 2), yTile - (pxBase / 2) };
	Coord C = { xTile + pxBase, yTile };
	Coord D = { xTile + (pxBase / 2), yTile + (pxBase / 4) };

	// Calcul des coordonnées des vecteurs de la tile
	Vector AB = { B.x - A.x, B.y - A.y };
	Vector AM = { mx - A.x, my - A.y };
	Vector BC = { C.x - B.x, C.y - B.y };
	Vector BM = { mx - B.x, my - B.y };
	Vector DC = { C.x - D.x, C.y - D.y };
	Vector DM = { mx - D.x, my - D.y };
	Vector AD = { D.x - A.x, D.y - A.y };
	Vector A2M = { mx - A.x, my - A.y };
	cpAB = crossProduct(AB, AM);
	cpBC = crossProduct(BC, BM);
	cpDC = crossProduct(DC, DM);
	cpAD = crossProduct(AD, A2M);

	// Sélection de la case sélectionnée en fonction de la position relative du clic et des vecteurs
	if (cpAB > 0){
		xIndex--;
	} else if (cpBC > 0){
		yIndex++;
	} else if (cpDC < 0){
		xIndex++;
	} else if (cpAD < 0){
		yIndex--;
	}

	if (xIndex > xSize-1 || yIndex > ySize-1 || xIndex < 0 || yIndex < 0) return 0;

	printf("[GRAPHICS] Case sélectionnée : %d, %d\n", xIndex, yIndex);
	(*(grid+xIndex*xSize+yIndex)).selected = 1;

	return 1;
}

int displayMap(SDL_Renderer *renderer, int x, int y, int pxBase, Tile * grid, int xSize, int ySize)
// Display the map
{
    SDL_Rect imgDestRect;

	SDL_Texture *block = NULL,
				*s_block = NULL,
				*water_block = NULL;

	if (pxBase == 64){
		block = tile;
		s_block = sb_tile;
		water_block = water_tile;
	} else {
		block = tile_big;
		s_block = sb_big_tile;
		water_block = water_big_tile;
	}

	/* Le fond de la fenêtre sera blanc */
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
	SDL_RenderClear(renderer);

    for (int i=0; i < xSize; i++){
        for (int j=(ySize-1); j >= 0; j--){

			imgDestRect.x = x+(j+1)*(pxBase/2)+(i+1)*(pxBase/2);
			imgDestRect.y = y+i*(pxBase/4)+(ySize-j)*(pxBase/4);

			if ((*(grid+i*xSize+j)).tile_id == 1){
				SDL_QueryTexture(water_block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
				SDL_RenderCopy(renderer, water_block, NULL, &imgDestRect);
			} else if ((*(grid+i*xSize+j)).tile_id != 0){
				if ((*(grid+i*xSize+j)).selected){
					SDL_QueryTexture(s_block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
					SDL_RenderCopy(renderer, s_block, NULL, &imgDestRect);
				} else {
					SDL_QueryTexture(block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
					SDL_RenderCopy(renderer, block, NULL, &imgDestRect);
				}

				/*/ -- DEBUG Affichage des indices des tuiles --
				char pos[6];
				sprintf(pos, "%d,%d", i, j);
				displayText(renderer, imgDestRect.x+(pxBase/2)-10, imgDestRect.y+(pxBase/4), (pxBase/64)*10, pos, "../inc/font/Pixels.ttf", 255, 50, 50);
				// -- DEBUG --*/
			}
        }
    }

	// -- DEBUG Affichage des coordonnées d'affichage de la map
	char str[12];
	sprintf(str, "%d, %d", x, y);
	displayText(renderer, 20, 20, 20, str, "../inc/font/Pixels.ttf", 255, 255, 255);
	// -- DEBUG --

	SDL_RenderPresent(renderer);

	return 1;
}
