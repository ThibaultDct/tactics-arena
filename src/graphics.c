#include <stdio.h>
#include "../GraphX/SDL2/include/SDL2/SDL.h"
#include "../GraphX/SDL2/include/SDL2/SDL_ttf.h"
#include "../GraphX/SDL2/include/SDL2/SDL_image.h"
#include "common.h"

int createWindow(int x, int y)
// Create a window with with x*y size (in px)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return ERROR;
    }

    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("Tactics Arena", SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                x,
                                                y,
                                                SDL_WINDOW_SHOWN);

    if (pWindow)
    {
        SDL_Delay(3000);
        SDL_DestroyWindow(pWindow);
    }
    else
    {
        printf("Erreur lors de la création de la fenêtre (%s)\n", SDL_GetError());
        return ERROR;
    }

    SDL_Quit();
    

    return OK;
}