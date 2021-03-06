/**
 * \file grid.c
 * \brief Contains all the functions relative to the grid of the game
 * \author Thibault DOUCET
 * \version 0.0.1
 * \date 28/01/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "grid.h"

/**
 * \fn void createGrid(Entity * grid, int x, int y)
 * \param grid A grid of entity
 * \param x Row's number
 * \param y Column's number
 * \brief Initialize the grid with x*y size in parameter with default entities
 */
void createGrid(Tile * grid, int seed, int x, int y)
// create the grid with x*y size
{
    srand(time(NULL));
    Entity * test = malloc(sizeof(Entity));
    test->act_points = 6;
    for (int i = 0; i < x*y; i++){
        grid[i].tile_id = rand()%seed;
        int t = rand()%5;
        grid[i].selected = 0;
        if (t == 1) grid[i].entity = test;
        else grid[i].entity = NULL;
    }
}

/**
 * \fn void debugGrid(Entity * grid, int x, int y)
 * \param grid Pointer to the begining of the entity matrix
 * \param x Row's number
 * \param y Column's number
 * \brief Display the entity ids of the matrix
 */
void debugGrid(Tile * grid, int x, int y)
// Debug by displaying the grid on the cmd
{
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            printf("%d ", (*(grid+i*x+j)).tile_id);
            if ((*(grid+i*x+j)).entity != NULL) printf("X");
        }
        printf("\n");
    }
}