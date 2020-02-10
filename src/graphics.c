#include <stdio.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"
#include "audio.h"

SDL_Color couleurNoire = {0, 0, 0};
SDL_Color couleurBlanc = {255, 255, 255};

void displayText(SDL_Renderer *renderer, int x, int y, int size, char *content, int r, int g, int b)
// Displays text on the window
{
	SDL_Surface *text = NULL;
	TTF_Font *police = NULL;
	SDL_Rect txtDestRect;

	SDL_Color color = {r, g, b};

	// Chargement de la police
	if( (police = TTF_OpenFont("../inc/font/Pixels.ttf", size)) == NULL){
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

int displaySprite(SDL_Renderer *renderer, char *sprite, int x, int y)
// Display a sprite on the window
{
	SDL_Rect imgDestRect;

	// Background image
	SDL_RWops *rwop=SDL_RWFromFile(sprite, "rb");
	sprite=IMG_LoadPNG_RW(rwop);
	if(!sprite) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_Texture *sprite_tex = SDL_CreateTextureFromSurface(renderer, (SDL_Surface*) sprite);
	if(!sprite_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface((SDL_Surface*) sprite); /* on a la texture, plus besoin de l'image */

	imgDestRect.x = x;
	imgDestRect.y = y;
	SDL_QueryTexture(sprite_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
	SDL_RenderCopy(renderer, sprite_tex, NULL, &imgDestRect);

	SDL_RenderPresent(renderer);

	return 1;
}

int closeWindow(SDL_Window *pWindow, TTF_Font *police)
// Kill and close the window
{
	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);

	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
	Mix_Quit();
    SDL_Quit();

    return 0;
}

int createWindow(int x, int y, char *title)
// Create a window with with x*y size (in px)
{
    //Le pointeur vers la fenetre
	SDL_Window* pWindow = NULL;
	//Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *icon=NULL;
	SDL_Renderer *renderer=NULL;

	// Le pointeur vers notre police
	TTF_Font *police = NULL;

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
	pWindow = SDL_CreateWindow(title, 			  SDL_WINDOWPOS_UNDEFINED,
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
    SDL_RWops *rwopIcon=SDL_RWFromFile("../inc/img/TacticsArena.png", "rb");
    icon = IMG_LoadPNG_RW(rwopIcon);
    if (!icon) {
        printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
    }
    SDL_SetWindowIcon(pWindow, icon);


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

								/* Le fond de la fenêtre sera blanc */
                                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
								SDL_RenderClear(renderer);

								/* Background image */
								displaySprite(renderer, "../inc/img/menu2_720p.png", 0, 0);

								/* Start button */
								displaySprite(renderer, "../inc/img/start_button_256.png", 500, 300);

								/* Quit button */
								displaySprite(renderer, "../inc/img/quit_button_256.png", 515, 375);

								/* Bouton musique ON/OFF */
								if (music_playing){
									displaySprite(renderer, "../inc/img/music_on.png", x-175, y-200);
								} else {
									displaySprite(renderer, "../inc/img/music_off.png", x-175, y-200);
								}

								/* Affiche en gros Tactics Arena */
								displayText(renderer, 0, 0, 100, "Tactics Arena", 255, 255, 255);

							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:

						printf("X: %d | Y: %d\n", e.motion.x, e.motion.y);		// Debug console pos x & y on term

						// Bouton "Quit"
						if (e.motion.x >= 585 && e.motion.x <= 710 && e.motion.y >= 467 && e.motion.y <= 518)
						{
							closeWindow(pWindow, police);
						}

						// Switch musique ON/OFF
						else if (e.motion.x >= 1202 && e.motion.x <= 1250 && e.motion.y >= 627 && e.motion.y <= 680)
						{
							if (music_playing)
							{
								music_playing = 0;
								pauseMenuMusic();
								displaySprite(renderer, "../inc/img/music_off.png", x-175, y-200);
							}
							else
							{
								music_playing = 1;
								resumeMenuMusic();
								displaySprite(renderer, "../inc/img/music_on.png", x-175, y-200);
							}
						}
					break;
				}
			}
		}
	} else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	return 1;
}