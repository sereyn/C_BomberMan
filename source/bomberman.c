#include "bomberman.h"

Bomberman initBomberman(int gridSize, Coord gridDimensions){
  Bomberman bbm;
  bbm.gridSize = gridSize;
  bbm.gridDimensions = gridDimensions;
  /*
    Initialise the sprites
    Then load the sprites using newSprite
  */
  bbm.sprites = initSprites();
  bbm.sprBlock = newSprite(&(bbm.sprites), "block.png", bbm.gridSize, bbm.gridSize);
  bbm.sprFloor = newSprite(&(bbm.sprites), "floor.png", bbm.gridSize, bbm.gridSize);
  /* Initialise the objects according to their sprites */
  bbm.floors = initObjects(bbm.sprFloor);
  bbm.blocks = initObjects(bbm.sprBlock);
  return bbm;
}

void drawAll(const Bomberman bbm){
  /* Draw all the objects */
  drawObjects(bbm.floors);
  drawObjects(bbm.blocks);
}

void freeBomberman(Bomberman bbm){
  /* Free all the allocated memory bomberman knows about */
  freeObjects(bbm.floors);
  freeObjects(bbm.blocks);
  freeSprites(bbm.sprites);
}
