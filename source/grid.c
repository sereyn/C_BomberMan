#include "grid.h"

void initGrid(int size, Coord dimensions){
	Grid grid;

	grid.size = size;
	grid.dimensions = dimensions;

	return grid;
}