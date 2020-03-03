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


#define _NB_TEXTURES_ 50

int isInSaveMenu = 0;
int isInLoadMenu = 0;

// Textures table
TabTexture textures[50];

// Contains the name of the map the user wants to save
char mapName[50] = "map_";
char *composition;
int mapNameIndex;
Sint32 cursor;
Sint32 selection_len;

void freeTextures(TabTexture * textures)
// Free all the textures in the given textures table
{
	int nbTextures = sizeof(textures) / sizeof(SDL_Texture*);

	for (int i=0; i < nbTextures; i++)
	{
		if (textures[i].texture != NULL)
		{
			SDL_DestroyTexture(textures[i].texture);
			textures[i].texture = NULL;
		}
	}
}

int loadEditorTextures(SDL_Renderer * renderer, TabTexture * textures)
// Load all the map related textures
{
	int index = 0;

	printf("[GRAPHICS] Effacement des textures pré-existantes...\n");

	freeTextures(textures);

	printf("[GRAPHICS] Chargement des textures du jeu...\n");

    // Loading blank pattern texture (64px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/blank_64.png"));
	textures[index++].texture_name = "blank_pattern";

	// Loading non-selected pattern texture (64px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/block_64.png"));
	textures[index++].texture_name = "pattern";

	// Loading red selected pattern texture (64px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/block_red_64.png"));
	textures[index++].texture_name = "sr_pattern";

	// Loading blue selected pattern texture (64px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/block_blue_64.png"));
	textures[index++].texture_name = "sb_pattern";

	// Loading water block texture (64px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/water_64.png"));
	textures[index++].texture_name = "water_pattern";

	// Loading sand block texture (64px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/sand_64.png"));
	textures[index++].texture_name = "sand_pattern";

    // Loading blank pattern texture (128px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/blank_128.png"));
	textures[index++].texture_name = "blank_big_pattern";

	// Loading non-selected pattern texture (128px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/block_128.png"));
	textures[index++].texture_name = "pattern_big";

	// Loading red selected pattern texture (128px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/block_red_128.png"));
	textures[index++].texture_name = "sr_big_pattern";

	// Loading blue selected pattern texture (128px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/block_blue_128.png"));
	textures[index++].texture_name = "sb_big_pattern";

	// Loadding water block texture (128px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/water_128.png"));
	textures[index++].texture_name = "water_big_pattern";

	// Loading sand block texture (128px)
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/sand_128.png"));
	textures[index++].texture_name = "sand_big_pattern";

	// Loading block selection interface texture
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/block_interface.png"));
	textures[index++].texture_name = "interface";

	// Loading eraser texture
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/eraser_64.png"));
	textures[index++].texture_name = "eraser";

	// Loading selection hover texture
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/editor_selection.png"));
	textures[index++].texture_name = "selection";

	// Loading green button texture
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/ok_button.png"));
	textures[index++].texture_name = "ok_button";

	// Loading orange button texture
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/load_button.png"));
	textures[index++].texture_name = "load_button";

	// Loading red button texture
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/cancel_button.png"));
	textures[index++].texture_name = "cancel_button";

	// Loading blur effect texture
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/blur.png"));
	textures[index++].texture_name = "blur";

	// Loading save menu texture
	textures[index].texture = loadTexture(renderer, loadImage("../inc/img/saveMenu.png"));
	textures[index++].texture_name = "save_menu";

	printf("[GRAPHICS] %d texture(s) chargée(s) !\n", index+1);

	return index+1;
}

int displaySaveMenu(SDL_Renderer * renderer, Tile * grid, int xWinSize, int yWinSize, char * mapName, int save)
// Display a save map menu and save the map
{
	int xPos = (xWinSize/2)-300;
	int yPos = (yWinSize/2)-60;
	int yOpPos = yPos + 120;

	displaySprite(renderer, getTexture(textures, "blur"), 0, 0);
	displaySprite(renderer, getTexture(textures, "save_menu"), xPos, yPos);
	if (save == 1)	displayText(renderer, xPos+10, yPos+5, 20, "Enregistrer la map...", "../inc/font/Pixels.ttf", 255, 255, 255);
	else			displayText(renderer, xPos+10, yPos+5, 20, "Charger la map...", "../inc/font/Pixels.ttf", 255, 255, 255);
	displayText(renderer, xPos+10, yOpPos-25, 20, "[ENTER] pour valider, [ESC] pour annuler", "../inc/font/Pixels.ttf", 255, 255, 255);
	if (mapName != NULL) displayText(renderer, xPos+40, yPos+55, 20, mapName, "../inc/font/Pixels.ttf", 0, 0, 0);

	return 1;
}

int saveMap(Tile * grid, const char * name)
{
	char mapName[20];

	sprintf(mapName, "../maps/%s", name);

	FILE * map;
	map = fopen(mapName, "wb");
	fwrite(grid, sizeof(Tile)*10*10, 1, map);

	fclose(map);

	return 1;
}

int loadMap(Tile * grid, const char * name)
// Load a map
{
	char mapName[20];

	sprintf(mapName, "../maps/%s", name);

	FILE * map;
	map = fopen(mapName, "rb");
	fread(grid, sizeof(Tile)*10*10, 1, map);

	fclose(map);

	return 1;
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

int displayEditorMap(SDL_Renderer *renderer, int x, int y, int pxBase, Tile * grid, int xSize, int ySize, int select, int xWinSize, int yWinSize)
// Display the map
{
	Coord selectionPos;
    SDL_Rect imgDestRect;
	SDL_Texture *block = NULL,
                *b_block = NULL,
				*s_block = NULL,
				*sr_block = NULL,
				*water_block = NULL,
				*sand_block = NULL;

	if (pxBase == 64){
        b_block = getTexture(textures, "blank_pattern");
		block = getTexture(textures, "pattern");
		s_block = getTexture(textures, "sb_pattern");
		sr_block = getTexture(textures, "sr_pattern");
		water_block = getTexture(textures, "water_pattern");
		sand_block = getTexture(textures, "sand_pattern");
	} else {
        b_block = getTexture(textures, "blank_big_pattern");
		block = getTexture(textures, "pattern_big");
		s_block = getTexture(textures, "sb_big_pattern");
		sr_block = getTexture(textures, "sr_big_pattern");
		water_block = getTexture(textures, "water_big_pattern");
		sand_block = getTexture(textures, "sand_big_pattern");
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
			else if ((*(grid+i*xSize+j)).tile_id == 4)
			{
				SDL_QueryTexture(sand_block, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
				SDL_RenderCopy(renderer, sand_block, NULL, &imgDestRect);
			}
        }
    }

	displaySprite(renderer, getTexture(textures, "interface"), 0, 0);
	displaySprite(renderer, getTexture(textures, "eraser"), 10, 50);
	displaySprite(renderer, getTexture(textures, "pattern"), 126, 50);
	displaySprite(renderer, getTexture(textures, "sr_pattern"), 10, 124);
	displaySprite(renderer, getTexture(textures, "water_pattern"), 126, 124);
	displaySprite(renderer, getTexture(textures, "sand_pattern"), 10, 198);

	if (select%2 == 0)		selectionPos.x = 10;
	else					selectionPos.x = 126;
	selectionPos.y = ceil(select/2)*74+50;
	displaySprite(renderer, getTexture(textures, "selection"), selectionPos.x, selectionPos.y);

	// Boutons
	displaySprite(renderer, getTexture(textures, "cancel_button"), 0, yWinSize-120);
	displayText(renderer, 10, yWinSize-110, 20, "QUITTER", "../inc/font/Pixels.ttf", 255, 255, 255);
	displaySprite(renderer, getTexture(textures, "load_button"), 0, yWinSize-80);
	displayText(renderer, 10, yWinSize-70, 20, "OUVRIR UNE MAP", "../inc/font/Pixels.ttf", 255, 255, 255);
	displaySprite(renderer, getTexture(textures, "ok_button"), 0, yWinSize-40);
	displayText(renderer, 10, yWinSize-30, 20, "ENREGISTRER", "../inc/font/Pixels.ttf", 255, 255, 255);

	displayText(renderer, 20, 20, 20, "----- BLOCS -----", "../inc/font/Pixels.ttf", 255, 255, 255);

	// -- DEBUG Affichage des coordonnées d'affichage de la map
	char str[12];
	sprintf(str, "%d, %d", x, y);
	displayText(renderer, 220, 20, 20, str, "../inc/font/Pixels.ttf", 255, 255, 255);
	// -- DEBUG --

	if (isInSaveMenu == 1) displaySaveMenu(renderer, grid, xWinSize, yWinSize, mapName, 1);
	if (isInLoadMenu == 1) displaySaveMenu(renderer, grid, xWinSize, yWinSize, mapName, 0);

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
	int XPOS = 400;
	int YPOS = 170;

	// x and y sizes of the window
	int xWinSize;
	int yWinSize;

	// Block selected
	int SELECT = 1;

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0 ) {
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

		loadEditorTextures(renderer, textures);

		SDL_GetWindowSize(pWindow, &xWinSize, &yWinSize);

		/* Le fond de la fenêtre sera blanc */
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_Delay(1);

		displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);

		SDL_RenderPresent(renderer);

		int running = 1;
		SDL_StartTextInput();
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

								SDL_GetWindowSize(pWindow, &xWinSize, &yWinSize);

								/* Le fond de la fenêtre sera blanc */
                				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderClear(renderer);

								SDL_Delay(1);

								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);

								SDL_RenderPresent(renderer);

							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:

						printf("X: %d | Y: %d\n", e.motion.x, e.motion.y);		// Debug console pos x & y on term
						if (e.motion.x <= 200)
						{
							if (e.motion.x >= 10 && e.motion.x <= 74 && e.motion.y >= 50 && e.motion.y <= 114)							SELECT = 0;
							else if (e.motion.x >= 126 && e.motion.x <= 190 && e.motion.y >= 50 && e.motion.y <= 114)					SELECT = 1;
							else if (e.motion.x >= 10 && e.motion.x <= 74 && e.motion.y >= 124 && e.motion.y <= 188)					SELECT = 2;
							else if (e.motion.x >= 126 && e.motion.x <= 190 && e.motion.y >= 124 && e.motion.y <= 188)					SELECT = 3;
							else if (e.motion.y >= 10 && e.motion.x <= 74 && e.motion.y >= 198 && e.motion.y <= 262)					SELECT = 4;
							else if (e.motion.x >= 0 && e.motion.x <= 200 && e.motion.y >= yWinSize-40 && e.motion.y <= yWinSize)		isInSaveMenu = 1;
							else if (e.motion.x >= 0 && e.motion.x <= 200 && e.motion.y >= yWinSize-80 && e.motion.y <= yWinSize-40) 	loadMap(grid, "map_plains");
							else if (e.motion.x >= 0 && e.motion.x <= 200 && e.motion.y >= yWinSize-120 && e.motion.y <= yWinSize-80)
							{
								closeWindow(pWindow);
								freeTextures(textures);
							}
						}
						else
						{
							if (!isInSaveMenu) changeTile(grid, XPOS, YPOS, e.motion.x, e.motion.y, PX, xSize, ySize, SELECT);
						}
						displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);

					break;
					case SDL_MOUSEWHEEL:
						if (e.wheel.y > 0)		// Scroll UP
						{
							if (PX == 64){
								PX = 128;
								printf("[GRAPHICS] Zoom In\n");
								XPOS *= 2;
								YPOS *= 2;
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
							}
						} else {				// Scroll DOWN
							if (PX == 128){
								PX = 64;
								printf("[GRAPHICS] Zoom Out\n");
								XPOS /= 2;
								YPOS /= 2;
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
							}
						}
					break;
					case SDL_KEYDOWN:
						if (isInSaveMenu == 0){
							switch(e.key.keysym.sym)
							{
								case SDLK_KP_PLUS: 	// "+" key
									if (PX == 64){
										PX = 128;
										printf("[GRAPHICS] Zoom In\n");
										XPOS *= 2;
										YPOS *= 2;
										displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
									}
									break;
								case SDLK_KP_MINUS:	// "-" key
									if (PX == 128){
										PX = 64;
										printf("[GRAPHICS] Zoom Out\n");
										XPOS /= 2;
										YPOS /= 2;
										displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
									}
									break;
								case SDLK_z:		// "z" key
									YPOS += (10*(PX/64));
									displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
									break;
								case SDLK_q:		// "q" key
									XPOS += (10*(PX/64));
									displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
									break;
								case SDLK_s:		// "s" key
									YPOS -= (10*(PX/64));
									displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
									break;
								case SDLK_d:		// "d" key
									XPOS -= (10*(PX/64));
									displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
									break;
							}
						}
						else
						{
							if (e.key.keysym.sym == SDLK_BACKSPACE)
							{
								if (strlen(mapName) > 4){
									mapName[strlen(mapName)-1] = '\0';
									displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
								}
							}
							else if (e.key.keysym.sym == SDLK_RETURN)
							{
								saveMap(grid, mapName);
								isInSaveMenu = 0;
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
							}
							else if (e.key.keysym.sym == SDLK_ESCAPE)
							{
								isInSaveMenu = 0;
								displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
							}
						}
						
					break;
					case SDL_TEXTINPUT:
						if (isInSaveMenu == 1)
						{
							strcat(mapName, e.text.text);
							displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
						}
					break;
					case SDL_TEXTEDITING:
						if (isInSaveMenu == 1)
						{
							composition = e.edit.text;
							cursor = e.edit.start;
							selection_len = e.edit.length;
							displayEditorMap(renderer, XPOS, YPOS, PX, grid, xSize, ySize, SELECT,  xWinSize, yWinSize);
						}
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
		freeTextures(textures);
	} else {
		fprintf(stderr,"[GRAPHICS] Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	return 1;
}