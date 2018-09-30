#include "bomberman.h"

Bomberman initBomberman(int gridSize, Coord gridDimensions){
  Bomberman bbm;
  debug(0, "Creating bomberman\n");
  /* Init grid */
  bbm.grid = initGrid(gridSize, gridDimensions);
  /*
    Initialise the sprites
    Then load the sprites using newSprite
  */
  debug(0, "Loading sprites...\n");
  bbm.sprites = initSprites();
  bbm.sprBlock = newSprite(&(bbm.sprites), "block.png", bbm.grid.size, bbm.grid.size);
  bbm.sprFloor = newSprite(&(bbm.sprites), "floor.png", bbm.grid.size, bbm.grid.size);
  bbm.sprBox = newSprite(&(bbm.sprites), "box.png", bbm.grid.size, bbm.grid.size);
  /* Initialise the objects according to their sprites */
  bbm.floors = initObjects(bbm.sprFloor, 'F');
  bbm.blocks = initObjects(bbm.sprBlock, 'B');
  bbm.boxes = initObjects(bbm.sprBox, 'C');
  /* Initialise the termGrid */
  bbm.termGrid = initTermGrid(gridSize, gridDimensions);
  /* Initialise editor */
  bbm.editor = initEditor(&bbm.grid);
  return bbm;
}

void drawAll(const Bomberman bbm){
  /* Fills the termGrid with zeros */
  resetTermGrid(bbm.termGrid);
  /* Draw all the objects (which will also prepare the termGrid) */
  drawObjects(bbm.floors, bbm.termGrid);
  drawObjects(bbm.blocks, bbm.termGrid);
  drawObjects(bbm.boxes, bbm.termGrid);
  /* Draw the equivalent result into the terminal */
  drawTermGrid(bbm.termGrid);
}

void freeBomberman(Bomberman bbm){
  debug(0, "Free the allocated memory\n");
  /* Free all the allocated memory bomberman knows about */
  freeObjects(bbm.floors);
  freeObjects(bbm.blocks);
  freeObjects(bbm.boxes);
  freeSprites(bbm.sprites);
  freeTermGrid(bbm.termGrid);
}
