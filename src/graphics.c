#include <stdio.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"
#include "audio.h"
#include "map.h"
#include "struct.h"

#define XPOS 500			// x position of the grid
#define YPOS 100			// y position of the grid

SDL_Texture *background = NULL,
			*start_button = NULL,
			*quit_button = NULL,
			*music_on = NULL,
			*music_off = NULL;

SDL_Surface * loadImage(const char * img)
// Load a PNG image into a surface
{
	SDL_RWops *rwop = NULL;
	SDL_Surface *surface = NULL;

	rwop=SDL_RWFromFile(img, "rb");
	surface=IMG_LoadPNG_RW(rwop);
	if(!surface) {
		printf("loadImage error while loading %s : %s\n", img, IMG_GetError());
		exit(EXIT_FAILURE);
	} else {
		printf("[GRAPHICS] Loading image %s... SUCCESS\n", img);
	}

	SDL_FreeRW(rwop);

	return surface;
}

SDL_Texture * loadTexture(SDL_Renderer * renderer, SDL_Surface * surface)
// Create a texture from a surface
{
	SDL_Texture * texture = NULL;

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture){
		fprintf(stderr, "loadTexture error while creating texture : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	} else {
		printf("[GRAPHICS] Creating texture from surface... SUCCESS\n");
	}

	return texture;
}

void loadMenuTextures(SDL_Renderer *renderer)
// Load all the textures needed for the menu
{
	// == Loading background ==
	background = loadTexture(renderer, loadImage("../inc/img/menu2_720p.png"));

	// == Loading start button ==
	start_button = loadTexture(renderer, loadImage("../inc/img/start_button_256.png"));

	// == Loading quit button ==
	quit_button = loadTexture(renderer, loadImage("../inc/img/quit_button_256.png"));

	// == Loading music ON switch ==
	music_on = loadTexture(renderer, loadImage("../inc/img/music_on.png"));

	// == Loading music OFF switch ==
	music_off = loadTexture(renderer, loadImage("../inc/img/music_off.png"));

}

void freeTextures()
// Free all the textures loaded
{
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(start_button);
	SDL_DestroyTexture(quit_button);
	SDL_DestroyTexture(music_on);
	SDL_DestroyTexture(music_off);
}

void displayText(SDL_Renderer *renderer, int x, int y, int size, char *content, char *text_police, int r, int g, int b)
// Displays text on the window
{
	SDL_Surface *text = NULL;
	TTF_Font *police = NULL;
	SDL_Rect txtDestRect;

	SDL_Color color = {r, g, b};

	// Chargement de la police
	if( (police = TTF_OpenFont(text_police, size)) == NULL){
		fprintf(stderr, "Erreur chargement initial font : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	// Création de la surface à partir du texte
	text = TTF_RenderUTF8_Blended(police, content, color);
	if(!text){
		fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// Création de la texture à partir de la surface
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_Texture *text_tex = SDL_CreateTextureFromSurface(renderer, text);
	if(!text_tex){
		fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(text);
	SDL_QueryTexture(text_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));

	txtDestRect.x = x;
	txtDestRect.y = y;

	/* Ajout du texte en noir */
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderCopy(renderer, text_tex, NULL, &txtDestRect);

	SDL_RenderPresent(renderer);

	TTF_CloseFont(police);
}

int displaySprite(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
// Display a sprite on the window
{
	SDL_Rect imgDestRect;

	imgDestRect.x = x;
	imgDestRect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
	SDL_RenderCopy(renderer, texture, NULL, &imgDestRect);

	SDL_RenderPresent(renderer);

	return 1;
}

int closeWindow(SDL_Window *pWindow)
// Kill and close the window
{
	SDL_DestroyWindow(pWindow);
	TTF_Quit();
	Mix_Quit();
  	SDL_Quit();

    return 0;
}

int createGameWindow(int x, int y)
// Create a window with with x*y size (in px)
{
    //Le pointeur vers la fenetre
	SDL_Window* pWindow = NULL;
	SDL_Renderer *renderer=NULL;

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
	pWindow = SDL_CreateWindow("Tactics Arena", 	SDL_WINDOWPOS_UNDEFINED,
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

	// Launcher icon
    SDL_SetWindowIcon(pWindow, loadImage("../inc/img/TacticsArena.png"));

	if( pWindow )
	{
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

								loadMapTextures(renderer);

								/* Le fond de la fenêtre sera blanc */
                				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderClear(renderer);

								displayMap(renderer, XPOS, YPOS);

								SDL_RenderPresent(renderer);

							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:

						printf("X: %d | Y: %d\n", e.motion.x, e.motion.y);		// Debug console pos x & y on term
						if (e.motion.x <= 10*64+XPOS && e.motion.y <= 10*64+YPOS && e.motion.x >= XPOS && e.motion.y >= YPOS){
							displayMap(renderer, XPOS, YPOS);
							setSelected(renderer, (e.motion.x-XPOS)/64, (e.motion.y-YPOS)/64, XPOS, YPOS);
						}
					break;
					case SDL_MOUSEMOTION:
						if (e.motion.x >= 10 && e.motion.y >= 10)
						{

						}
					break;
				}
			}
		}
		closeWindow(pWindow);
	} else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	return 1;
}

int displayMenu(int x, int y)
// Create a window with with x*y size (in px)
{
    //Le pointeur vers la fenetre
	SDL_Window* pWindow = NULL;
	SDL_Renderer *renderer=NULL;

	// La musique est activée de base
	int music_playing = 1;

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
	pWindow = SDL_CreateWindow("Tactics Arena - Menu", 	SDL_WINDOWPOS_UNDEFINED,
												  		SDL_WINDOWPOS_UNDEFINED,
												  		x,
												  		y,
												  		SDL_WINDOW_SHOWN);

	if(!pWindow){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}

	// Launcher icon
    SDL_SetWindowIcon(pWindow, loadImage("../inc/img/TacticsArena.png"));

	if( pWindow )
	{
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

								loadMenuTextures(renderer);

								/* Le fond de la fenêtre sera blanc */
                				//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
								//SDL_RenderClear(renderer);

								/* Background image */
								displaySprite(renderer, background, 0, 0);

								/* Start button */
								displaySprite(renderer, start_button, 500, 300);

								/* Quit button */
								displaySprite(renderer, quit_button, 515, 375);

								/* Bouton musique ON/OFF */
								if (music_playing){
									displaySprite(renderer, music_on, x-175, y-200);
								} else {
									displaySprite(renderer, music_off, x-175, y-200);
								}

								/* Affiche en gros Tactics Arena */
								displayText(renderer, 300, 200, 100, "Tactics Arena", "../inc/font/Blox2.ttf", 255, 255, 255);

								/* Mentions de bas de menu */
								displayText(renderer, 5, y-20, 15, "Projet L2 Informatique - BUTEL CHAUVIN DOUCET LAFAY", "../inc/font/Pixels.ttf", 255, 255, 255);
							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:

						printf("X: %d | Y: %d\n", e.motion.x, e.motion.y);		// Debug console pos x & y on term

						// Bouton "Start"
						if (e.motion.x >= 569 && e.motion.x <= 730 && e.motion.y >= 394 && e.motion.y <= 443)
						{
							closeWindow(pWindow);
							freeTextures();
							createGameWindow(1920, 1080);
						}

						// Bouton "Quit"
						else if (e.motion.x >= 585 && e.motion.x <= 710 && e.motion.y >= 467 && e.motion.y <= 518)
						{
							closeWindow(pWindow);
							freeTextures();
						}

						// Switch musique ON/OFF
						else if (e.motion.x >= 1202 && e.motion.x <= 1250 && e.motion.y >= 627 && e.motion.y <= 680)
						{
							if (music_playing)
							{
								music_playing = 0;
								pauseMenuMusic();
								displaySprite(renderer, music_off, x-175, y-200);
							}
							else
							{
								music_playing = 1;
								resumeMenuMusic();
								displaySprite(renderer, music_on, x-175, y-200);
							}
						}
					break;
				}
			}
		}
		closeWindow(pWindow);
		freeTextures();
	} else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	return 1;
}
