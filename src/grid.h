#ifndef grid_h
#define grid_h

#include "struct.h"

void createGrid(Entity * grid, int x, int y);
void debugGrid(Entity * grid, int x, int y);
Entity getEntity(Entity * grid, int size, int x, int y);

#endif