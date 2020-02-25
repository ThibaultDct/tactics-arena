#include <stdio.h>
#include "grid.h"

/**
 * \fn Entity getEntity(Entity * grid, int size, int x, int y)
 * \param grid Pointer to the begining of the entity matrix
 * \param size Size of the grid
 * \param x Row's number
 * \param y Column's number
 * \return The entity at x:y coordinates
 * \brief Return the entity at position x:y of the matrix "grid"
 */
Tile getTile(Tile * grid, int size, int x, int y)
// Return the entity at the x:y position in the grid 
{
    return grid[x*size+y];
}

/**
 * \fn Entity getId(Entity entity)
 * \param entity Entity that id will be returned
 * \return The id of the entity
 * \brief Return the id of the entity
 */
int getTileId(Tile tile)
// Return the id of the entity 
{
    return tile.tile_id;
}