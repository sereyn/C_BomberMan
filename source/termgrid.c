#include "termgrid.h"

TermGrid initTermGrid(int gridSize, Coord gridDimensions){
  /* Initializing the grid and its members such has marginTop */
  int i = 0;
  TermGrid termGrid;
  termGrid.dimensions = gridDimensions;
  termGrid.size = gridSize;
  termGrid.marginTop = MLV_get_window_height()/gridSize-gridDimensions.y;
  termGrid.grid = malloc(termGrid.dimensions.x*termGrid.dimensions.y*sizeof(*(termGrid.grid)));
  for(; i < termGrid.dimensions.y; ++i)
    termGrid.grid[i] = malloc(termGrid.dimensions.x*sizeof(**(termGrid.grid)));
  return termGrid;
}

void resetTermGrid(TermGrid termGrid){
  /* Filling the termGrid with zeros */
  int x, y;
  for(y = 0; y < termGrid.dimensions.y; ++y){
    for(x = 0; x < termGrid.dimensions.x; ++x)
      termGrid.grid[y][x] = '0';
  }
}

void drawTermGrid(TermGrid termGrid){
  int x, y;
  int debugLevel = 5;
  /* First we clear the terminal using an escape sequence */
  debug(debugLevel, "\033[H\033[J");
  /* Then we loop through the whole termGrid to correctly print it */
  for(y = 0; y < termGrid.dimensions.y; ++y){
    for(x = 0; x < termGrid.dimensions.x; ++x){
      debug(debugLevel, "%c", termGrid.grid[y][x]);
    }
    debug(debugLevel, "\n");
  }
}

void freeTermGrid(TermGrid termGrid){
  int i = 0;
  for(; i < termGrid.dimensions.y; ++i)
    free(termGrid.grid[i]);
  free(termGrid.grid);
}
