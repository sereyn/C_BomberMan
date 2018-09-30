#include "grid.h"

Grid *initGrid(int size, Coord *dimensions, int marginTop){
  /* Initializing the grid and its members such has marginTop */
  int i = 0;
  Grid *grid = malloc(sizeof(Grid));
  grid->dimensions = dimensions;
  grid->size = size;
  grid->marginTop = marginTop;
  grid->grid = malloc(grid->dimensions->x*grid->dimensions->y*sizeof(char *));
  for(; i < grid->dimensions->y; ++i)
    grid->grid[i] = malloc(grid->dimensions->x*sizeof(char));
  return grid;
}

void resetGrid(Grid *grid){
  /* Filling the termGrid with zeros */
  int x, y;
  for(y = 0; y < grid->dimensions->y; ++y){
    for(x = 0; x < grid->dimensions->x; ++x)
      grid->grid[y][x] = '0';
  }
}

void printGrid(Grid *grid){
  int x, y;
  int debugLevel = 5;
  /* First we clear the terminal using an escape sequence */
  debug(debugLevel, "\033[H\033[J");
  /* Then we loop through the whole termGrid to correctly print it */
  for(y = 0; y < grid->dimensions->y; ++y){
    for(x = 0; x < grid->dimensions->x; ++x){
      debug(debugLevel, "%c", grid->grid[y][x]);
    }
    debug(debugLevel, "\n");
  }
}

void freeGrid(Grid *grid){
  /* We free the dynamically created memory */
  int i = 0;
  for(; i < grid->dimensions->y; ++i)
    free(grid->grid[i]);
  free(grid->dimensions);
  free(grid->grid);
  free(grid);
}
