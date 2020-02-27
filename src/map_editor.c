#include <stdio.h>
#include <math.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"
#include "graphics.h"
#include "struct.h"
#include "audio.h"
#include "map.h"

SDL_Texture *eraser = NULL,
			*blank_pattern = NULL,
            *pattern = NULL,
			*sr_pattern = NULL,
			*sb_pattern = NULL,
			*water_pattern = NULL,
            *blank_big_pattern = NULL,
			*pattern_big = NULL,
			*sr_big_pattern = NULL,
			*sb_big_pattern = NULL,
			*water_big_pattern = NULL,
			*interface = NULL,
			*selection = NULL;

void loadEditorTextures(SDL_Renderer * renderer)
// Load all the map related textures
{
    if (blank_pattern != NULL) 		SDL_DestroyTexture(blank_pattern), 		blank_pattern = NULL;
	if (pattern != NULL) 			SDL_DestroyTexture(pattern), 			pattern = NULL;
	if (sr_pattern != NULL) 		SDL_DestroyTexture(sr_pattern), 		sr_pattern = NULL;
	if (sb_pattern != NULL) 		SDL_DestroyTexture(sb_pattern), 		sb_pattern = NULL;
	if (water_pattern != NULL) 		SDL_DestroyTexture(water_pattern), 		water_pattern = NULL;
    if (blank_big_pattern != NULL) 	SDL_DestroyTexture(blank_big_pattern), 	blank_big_pattern = NULL;
	if (pattern_big != NULL) 		SDL_DestroyTexture(pattern_big), 		pattern_big = NULL;
	if (sr_big_pattern != NULL) 	SDL_DestroyTexture(sr_big_pattern), 	sr_big_pattern = NULL;
	if (sb_big_pattern != NULL) 	SDL_DestroyTexture(sb_big_pattern), 	sb_big_pattern = NULL;
	if (water_big_pattern != NULL) 	SDL_DestroyTexture(water_big_pattern), 	water_big_pattern = NULL;
	if (interface != NULL)			SDL_DestroyTexture(interface),			interface = NULL;
	if (eraser != NULL) 			SDL_DestroyTexture(eraser), 			eraser = NULL;
	if (selection != NULL) 			SDL_DestroyTexture(selection), 			selection = NULL;

	printf("[GRAPHICS] Chargement des textures du jeu...\n");

    // Loading blank pattern texture (64px)
    blank_pattern = loadTexture(renderer, loadImage("../inc/img/blank_64.png"));

	// Loading non-selected pattern texture (64px)
	pattern = loadTexture(renderer, loadImage("../inc/img/block_64.png"));

	// Loading red selected pattern texture (64px)
	sr_pattern = loadTexture(renderer, loadImage("../inc/img/block_red_64.png"));

	// Loading blue selected pattern texture (64px)
	sb_pattern = loadTexture(renderer, loadImage("../inc/img/block_blue_64.png"));

	// Loading water block texture (64px)
	water_pattern = loadTexture(renderer, loadImage("../inc/img/water_64.png"));

    // Loading blank pattern texture (128px)
    blank_big_pattern = loadTexture(renderer, loadImage("../inc/img/blank_128.png"));

	// Loading non-selected pattern texture (128px)
	pattern_big = loadTexture(renderer, loadImage("../inc/img/block_128.png"));

	// Loading red selected pattern texture (128px)
	sr_big_pattern = loadTexture(renderer, loadImage("../inc/img/block_red_128.png"));

	// Loading blue selected pattern texture (128px)
	sb_big_pattern = loadTexture(renderer, loadImage("../inc/img/block_blue_128.png"));

	// Loadding water block texture (128px)
	water_big_pattern = loadTexture(renderer, loadImage("../inc/img/water_128.png"));

	// Loading block selection interface texture
	interface = loadTexture(renderer, loadImage("../inc/img/block_interface.png"));

	// Loading eraser texture
	eraser = loadTexture(renderer, loadImage("../inc/img/eraser_64.png"));

	// Loading selection hover texture
	selection = loadTexture(renderer, loadImage("../inc/img/editor_selection.png"));
}

int changeTile(Tile * grid, int xpos, int ypos, int mx, int my, int pxBase, int xSize, int ySize, int toTile)
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
	(*(grid+xIndex*xSize+yIndex)).tile_id = toTile;

	return 1;
}

int displayEditorMap(SDL_Renderer *renderer, int x, int y, int pxBase, Tile * grid, int xSize, int ySize, int select)
// Display the map
{
	Coord selectionPos;
    SDL_Rect imgDestRect;
	SDL_Texture *block = NULL,
                *b_block = NULL,
				*s_block = NULL,
				*sr_block = NULL,
				*water_block = NULL;

	if (pxBase == 64){
        b_block = blank_pattern;
		block = pattern;
		s_block = sb_pattern;
		sr_block = sr_pattern;
		water_block = water_pattern;
	} else {
        b_block = blank_big_pattern;
		block = pattern_big;
		s_block = sb_big_pattern;
		sr_block = sr_big_pattern;
		water_block = water_big_pattern;
	}

	/* Le fond de la fenêtre sera blanc */
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
	SDL_RenderClear(renderer);

    for (int i=0; i < xSize; i++){
        for (int j=(ySize-1); j >= 0; j--){

			imgDestRect.x = x+(j+1)*(pxBase/2)+(i+1)*(pxBase/2);
			imgDestRect.y = y+i*(pxBase/4)+(ySize-j)*(pxBase/4);

			if ((*(grid+i*xSize+j)).tile_id == 0)
			{
				SDL_QueryTexture(b_block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
				SDL_RenderCopy(renderer, b_block, NULL, &imgDestRect);
			} 
			else if ((*(grid+i*xSize+j)).tile_id == 1)
			{
				if ((*(grid+i*xSize+j)).selected)
				{
					SDL_QueryTexture(s_block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
					SDL_RenderCopy(renderer, s_block, NULL, &imgDestRect);
				} 
				else
				{
					SDL_QueryTexture(block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
					SDL_RenderCopy(renderer, block, NULL, &imgDestRect);
				}

				/*/ -- DEBUG Affichage des indices des tuiles --
				char pos[6];
				sprintf(pos, "%d,%d", i, j);
				displayText(renderer, imgDestRect.x+(pxBase/2)-10, imgDestRect.y+(pxBase/4), (pxBase/64)*10, pos, "../inc/font/Pixels.ttf", 255, 50, 50);
				// -- DEBUG --*/
			}
			else if ((*(grid+i*xSize+j)).tile_id == 2)
			{
				SDL_QueryTexture(sr_block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
				SDL_RenderCopy(renderer, sr_block, NULL, &imgDestRect);
			}
			else if ((*(grid+i*xSize+j)).tile_id == 3)
			{
				SDL_QueryTexture(water_block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
				SDL_RenderCopy(renderer, water_block, NULL, &imgDestRect);
			} 
        }
    }

	displaySprite(renderer, interface, 0, 0);
	displaySprite(renderer, eraser, 10, 50);
	displaySprite(renderer, pattern, 126, 50);
	displaySprite(renderer, sr_pattern, 10, 124);
	displaySprite(renderer, water_pattern, 126, 124);

	if (select%2 == 0)		selectionPos.x = 10;
	else					selectionPos.x = 126;
	selectionPos.y = ceil(select/2)*74+50;
	displaySprite(renderer, selection, selectionPos.x, selectionPos.y);

	// -- DEBUG Affichage des coordonnées d'affichage de la map
	char str[12];
	sprintf(str, "%d, %d", x, y);
	displayText(renderer, 20, 20, 20, str, "../inc/font/Pixels.ttf", 255, 255, 255);
	// -- DEBUG --

	SDL_RenderPresent(renderer);

	return 1;
}

int createMapEditorWindow(int x, int y, Tile * grid, int xSize, int ySize)
// Create a window with with x*y size (in px)
{
    // Le pointeur vers la fenetre
	SDL_Window* pWindow = NULL;
	SDL_Renderer *renderer=NULL;

	// Resolution of a bloc texture (can be 64 or 128)
	int PX = 64;

	// x and y pos where map is displayed
	int XPOS = 300;
	int YPOS = 70;

	// Block selected
	int SELECT = 1;

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Tactics Arena - Editeur de map", 	SDL_WINDOWPOS_UNDEFINED,
												  					SDL_WINDOWPOS_UNDEFINED,
												  					x,
												  					y,
												  					SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if(!pWindow){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}

	setRendererDriver(renderer);

	// Launcher icon
    SDL_SetWindowIcon(pWindow, loadImage("../inc/img/TacticsArena.png"));

	if( pWindow )
	{

		loadEditorTextures(renderer);

		/* Le fond de la fenêtre sera blanc */
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_Delay(1);

		displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);

		SDL_RenderPresent(renderer);

		int running = 1;
		while(running) {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: running = 0;
					break;
					case SDL_WINDOWEVENT:
						switch(e.window.event){
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_HIDDEN:
							case SDL_WINDOWEVENT_SHOWN:

								/* Le fond de la fenêtre sera blanc */
                				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderClear(renderer);

								SDL_Delay(1);

								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);

								SDL_RenderPresent(renderer);

							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:

						printf("X: %d | Y: %d\n", e.motion.x, e.motion.y);		// Debug console pos x & y on term
						if (e.motion.x <= 200)
						{
							if (e.motion.x >= 10 && e.motion.x <= 74 && e.motion.y >= 50 && e.motion.y <= 114)	SELECT = 0;
							else if (e.motion.x >= 126 && e.motion.x <= 190 && e.motion.y >= 50 && e.motion.y <= 114)	SELECT = 1;
							else if (e.motion.x >= 10 && e.motion.x <= 74 && e.motion.y >= 124 && e.motion.y <= 188)	SELECT = 2;
							else if (e.motion.x >= 126 && e.motion.x <= 190 && e.motion.y >= 124 && e.motion.y <= 188)	SELECT = 3;
						}
						else
						{
							changeTile(grid, XPOS, YPOS, e.motion.x, e.motion.y, PX, xSize, ySize, SELECT);
						}
						displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);

					break;
					case SDL_MOUSEWHEEL:
						if (e.wheel.y > 0)		// Scroll UP
						{
							if (PX == 64){
								PX = 128;
								printf("[GRAPHICS] Zoom In\n");
								XPOS *= 2;
								YPOS *= 2;
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);
							}
						} else {				// Scroll DOWN
							if (PX == 128){
								PX = 64;
								printf("[GRAPHICS] Zoom Out\n");
								XPOS /= 2;
								YPOS /= 2;
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);
							}
						}
					break;
					case SDL_KEYDOWN:
						switch(e.key.keysym.sym)
						{
							case SDLK_KP_PLUS: 	// "+" key
								if (PX == 64){
									PX = 128;
									printf("[GRAPHICS] Zoom In\n");
									XPOS *= 2;
									YPOS *= 2;
									displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);
								}
								break;
							case SDLK_KP_MINUS:	// "-" key
								if (PX == 128){
									PX = 64;
									printf("[GRAPHICS] Zoom Out\n");
									XPOS /= 2;
									YPOS /= 2;
									displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);
								}
								break;
							case SDLK_z:		// "z" key
								YPOS += (10*(PX/64));
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);
								break;
							case SDLK_q:		// "q" key
								XPOS += (10*(PX/64));
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);
								break;
							case SDLK_s:		// "s" key
								YPOS -= (10*(PX/64));
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);
								break;
							case SDLK_d:		// "d" key
								XPOS -= (10*(PX/64));
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT);
								break;
						}
					break;
					case SDL_MOUSEMOTION:

						if (e.motion.x >= 10 && e.motion.y >= 10)
						{

						}

					break;
				}
			}
			SDL_Delay(16);
		}
		closeWindow(pWindow);
	} else {
		fprintf(stderr,"[GRAPHICS] Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	return 1;
}