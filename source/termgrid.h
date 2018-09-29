#ifndef TERMGRID
#define TERMGRID

#include <MLV/MLV_all.h>
#include "utils.h"
#include <stdlib.h>

typedef struct {
	char **grid;
	Coord dimensions;
	int size;
	int marginTop;
} TermGrid;

TermGrid initTermGrid(int gridSize, Coord gridDimensions);

void resetTermGrid(TermGrid termGrid);

void drawTermGrid(TermGrid termGrid);

void freeTermGrid(TermGrid termGrid);

#endif /* TERMGRID */