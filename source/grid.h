#ifndef GRID
#define GRID

#include "utils.h"
#include <stdlib.h>

typedef struct {
	char **grid;
	Coord *dimensions;
	int size;
	int marginTop;
} Grid;

Grid *initGrid(int size, Coord *dimensions, int marginTop);

/* Fills the terminal grid with zeros */
void resetGrid(Grid *);

/* Prints the grid in the terminal for debugging */
void printGrid(Grid *);

void freeGrid(Grid *);

#endif /* GRID */
