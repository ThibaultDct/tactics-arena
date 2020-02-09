#include <stdio.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_mixer.h"

Mix_Music* myMus;

int playMenuMusic()
// Play the menu music
{
    /* Initialisation */
    if (SDL_Init(SDL_INIT_AUDIO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    /* On ouvre le device audio */
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

    /* On charge la musique */
    myMus = Mix_LoadMUS("../inc/music/cascade.wav");

    /* On lance la musique */
    Mix_PlayMusic(myMus, 1);

    return 0;
}

int stopMenuMusic()
// Stop the menu music
{
     /* La musique est terminée, on la libère */
    Mix_FreeMusic(myMus);

    /* On libère le matériel */
    Mix_CloseAudio();

    return 0;
}