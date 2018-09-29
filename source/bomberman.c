#include "bomberman.h"

Bomberman initBomberman(int gridSize, Coord gridDimensions){
  Bomberman bbm;
  debug(0, "Creating bomberman\n");
  bbm.gridSize = gridSize;
  bbm.gridDimensions = gridDimensions;
  /*
    Initialise the sprites
    Then load the sprites using newSprite
  */
  debug(0, "Loading sprites...\n");
  bbm.sprites = initSprites();
  bbm.sprBlock = newSprite(&(bbm.sprites), "block.png", bbm.gridSize, bbm.gridSize);
  bbm.sprFloor = newSprite(&(bbm.sprites), "floor.png", bbm.gridSize, bbm.gridSize);
  /* Initialise the objects according to their sprites */
  bbm.floors = initObjects(bbm.sprFloor, 'F');
  bbm.blocks = initObjects(bbm.sprBlock, 'B');
  /* Initialise the termGrid */
  bbm.termGrid = initTermGrid(gridSize, gridDimensions);
  return bbm;
}

void drawAll(const Bomberman bbm){
  /* Fills the termGrid with zeros */
  resetTermGrid(bbm.termGrid);
  /* Draw all the objects (which will also prepare the termGrid) */
  drawObjects(bbm.floors, bbm.termGrid);
  drawObjects(bbm.blocks, bbm.termGrid);
  /* Draw the equivalent result into the terminal */
  drawTermGrid(bbm.termGrid);
}

void freeBomberman(Bomberman bbm){
  debug(0, "Free the allocated memory\n");
  /* Free all the allocated memory bomberman knows about */
  freeObjects(bbm.floors);
  freeObjects(bbm.blocks);
  freeSprites(bbm.sprites);
  freeTermGrid(bbm.termGrid);
}
