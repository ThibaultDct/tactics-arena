/**
 * \file grid.c
 * \brief Contains all the functions relative to the grid of the game
 * \author Thibault DOUCET
 * \version 0.0.1
 * \date 28/01/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "grid.h"

/**
 * \fn void createGrid(Entity * grid, int x, int y)
 * \param grid A grid of entity
 * \param x Row's number
 * \param y Column's number
 * \brief Initialize the grid with x*y size in parameter with default entities
 */
void createGrid(Entity * grid, int x, int y)
// create the grid with x*y size
{
    for (int i = 0; i < x*y; i++){
        grid[i].cha_id = i;
    }
}

/**
 * \fn void debugGrid(Entity * grid, int x, int y)
 * \param grid Pointer to the begining of the entity matrix
 * \param x Row's number
 * \param y Column's number
 * \brief Display the entity ids of the matrix
 */
void debugGrid(Entity * grid, int x, int y)
// Debug by displaying the grid on the cmd
{
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            printf("%d ", (*(grid+i*x+j)).cha_id);
        }
        printf("\n");
    }
}

/**
 * \fn Entity getEntity(Entity * grid, int size, int x, int y)
 * \param grid Pointer to the begining of the entity matrix
 * \param size Size of the grid
 * \param x Row's number
 * \param y Column's number
 * \return The entity at x:y coordinates
 * \brief Return the entity at position x:y of the matrix "grid"
 */
Entity getEntity(Entity * grid, int size, int x, int y)
// Return the entity at the x:y position in the grid 
{
    return grid[x*size+y];
}