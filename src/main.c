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

#define X 10
#define Y 10

/**
 * \fn int main(void)
 * \return void
 * \brief Main function
 */
int main()
{
    Entity grid[X][Y];                                  /**< Contains the pointer to the start of the matrix */
    Entity *matrix = &grid[0][0];

    createGrid((Entity *)grid, X, Y);
    debugGrid(matrix, X, Y);
    printf("Entity at pos %d:%d : %d\n", 5, 7, getEntity(matrix, X, 5, 7).cha_id);

    free(matrix);

    getchar();  // Wait for the user to press a key to end the program

    return 0;
}
