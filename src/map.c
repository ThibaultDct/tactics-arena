#include <stdio.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
#include "../SDL2/include/SDL2/SDL_ttf.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"
#include "graphics.h"
#include "struct.h"
#include "audio.h"

int setSelected(SDL_Renderer *renderer, int x, int y)
// Set the tile selected
{
	SDL_Rect imgDestRect;
    SDL_Surface *s_sprite = NULL;

	// Selected tile
	SDL_RWops *s_rwop=SDL_RWFromFile("../inc/img/tile_selected_64.png", "rb");
	s_sprite=IMG_LoadPNG_RW(s_rwop);
	if(!s_sprite) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_Texture *s_sprite_tex = SDL_CreateTextureFromSurface(renderer, (SDL_Surface*) s_sprite);
	if(!s_sprite_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface((SDL_Surface*) s_sprite); /* on a la texture, plus besoin de l'image */

	imgDestRect.x = x*64+10;
    imgDestRect.y = y*64+10;
	SDL_QueryTexture(s_sprite_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
	SDL_RenderCopy(renderer, s_sprite_tex, NULL, &imgDestRect);

	SDL_RenderPresent(renderer);
	
	return 1;
}

int displayMap(SDL_Renderer *renderer, int x, int y)
// Display the map
{
    SDL_Rect imgDestRect;
    SDL_Surface *sprite = NULL;

	// Unselected tile
	SDL_RWops *rwop=SDL_RWFromFile("../inc/img/tile_64.png", "rb");
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

    for (int i=0; i < 10; i++){
        for (int j=0; j < 10; j++){
            imgDestRect.x = x+i*64;
            imgDestRect.y = y+j*64;
			SDL_QueryTexture(sprite_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
			SDL_RenderCopy(renderer, sprite_tex, NULL, &imgDestRect);
        }
    }

	SDL_RenderPresent(renderer);
	return 1;
}