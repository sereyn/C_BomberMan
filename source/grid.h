#ifndef GRID
#define GRID

#include "utils.h"

typedef struct{
	int size;
	Coord dimensions;
} Grid;

Grid initGrid(int size, Coord dimensions);

#endif /* GRID */