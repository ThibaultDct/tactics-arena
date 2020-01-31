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
    //Marche pas pendant la construction de structures
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            grid[i*x+j].id = j;
        }
    }
}