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

#define X 10
#define Y 10

/**
 * \fn int main(void)
 * \return void
 * \brief Main function
 */
int main()
{
    Entity grid[X][Y];
    Entity *matrix = &grid[0][0];           /**< Contains the pointer to the start of the matrix */

    createGrid((Entity *)grid, X, Y);

    for (int i = 0; i < X; i++){
        for (int j = 0; j < Y; j++){
            printf("%d ", (*(matrix+i)).pdv);
        }
        printf("\n");
    }

    free(matrix);

    getchar();  // Wait for the user to press a key to end the program

    return 0;
}