/**
 * \file main.c
 * \brief Main program for TacticsArena
 * \details Contains main function
 * \author Thibault DOUCET
 * \version 0.0.1
 * \date 28/01/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "Socket_Server.h"
#include "struct.h"
#include "terrain.h"
#include "graphics.h"
#include "audio.h"
#include "menu.h"

#define X 100
#define Y 100

/**
 * \fn int main(void)
 * \return void
 * \brief Main function
 */
int main()
{   
    #if defined (WIN32)
    /*
    * Change the cmd codepage on Windows
    */
    system("chcp 65001");
    system("cls");
    #elif __unix__ || defined __APPLE_
    system("clear");
    #endif
    
    Tile grid[X][Y];                                  /**< Contains the pointer to the start of the matrix */
    Tile *matrix = &grid[0][0];

    int choix = 0;
    printf("Bienvenue dans le serveur :) \n");


    printf("Lancer le serveur (1) \n");
    printf("Lancer le client (2) \n");
    printf("Lancer le jeux (3) \n");
    printf("\nFaites votre choix : \n");
    scanf("%d", &choix);

    switch (choix) {
        case 1: startTCPSocketServ();
        break;
        case 2: startTCPSocketCli();
        break;
        case 3:
                createGrid((Tile *)grid, X, Y);
                playMenuMusic();
                if (displayMenu(1280, 720) == 2){
                    stopMenuMusic();
                    createGameWindow(1920,1980,matrix, X, Y);
                }
                debugGrid(matrix, X, Y);
                printf("Entity at pos %d:%d : %d\n", 5, 7, getTileId(getTile(matrix, X, 5, 7)));
                free(matrix);
        break;
  }

    

    

    getchar();  // Wait for the user to press a key to end the program

    return 0;
}
