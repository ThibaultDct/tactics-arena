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
#include "struct.h"
#include "entity.h"
#include "graphics.h"
#include "audio.h"

#define X 10
#define Y 10

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
    
    Entity grid[X][Y];                                  /**< Contains the pointer to the start of the matrix */
    Entity *matrix = &grid[0][0];

    int choix = 0;
    printf("Bienvenue dans le serveur :) \n");


    printf("Lancer le serveur (1) \n");
    printf("Lancer le client (2) \n");
    printf("Lancer le jeux (3) \n");
    printf("\nFaites votre choix : \n");
    scanf("%d", &choix);

    switch (choix) {
        case 1:startTCPSocketServ();break;
        case 2:startTCPSocketCli();break;
        case 3: playMenuMusic();
                displayMenu(1280, 720);
                stopMenuMusic();
                createGrid((Entity *)grid, X, Y);
                debugGrid(matrix, X, Y);
                printf("Entity at pos %d:%d : %d\n", 5, 7, getEntity(matrix, X, 5, 7).cha_id);
                free(matrix);break;
  }

    

    

    getchar();  // Wait for the user to press a key to end the program

    return 0;
}
