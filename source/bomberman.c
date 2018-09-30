#include "bomberman.h"

Bomberman *initBomberman(Grid *grid){
  Bomberman *bbm = malloc(sizeof(Bomberman));
  debug(0, "Creating bomberman\n");
  bbm->grid = grid;
  /*
    Initialise the sprites
    Then load the sprites using newSprite
  */
  debug(0, "Loading sprites...\n");
  bbm->sprites = initSprites();
  bbm->sprBlock = newSprite(bbm->sprites, "block.png", bbm->grid->size, bbm->grid->size);
  bbm->sprFloor = newSprite(bbm->sprites, "floor.png", bbm->grid->size, bbm->grid->size);
  bbm->sprBox = newSprite(bbm->sprites, "box.png", bbm->grid->size, bbm->grid->size);
  /* Initialise the objects according to their sprites */
  bbm->floors = initObjects(bbm->sprFloor, 'F');
  bbm->blocks = initObjects(bbm->sprBlock, 'B');
  bbm->boxes = initObjects(bbm->sprBox, 'C');
  return bbm;
}

void drawAll(Bomberman *bbm){
  /* Fills the grid with zeros */
  resetGrid(bbm->grid);
  /* Draws all the objects (which will also prepare the grid) */
  drawObjects(bbm->floors, bbm->grid);
  drawObjects(bbm->blocks, bbm->grid);
  drawObjects(bbm->boxes, bbm->grid);
  /* Prints the equivalent result into the terminal */
  printGrid(bbm->grid);
}

void freeBomberman(Bomberman *bbm){
  debug(0, "Free the allocated memory\n");
  /* Free all the allocated memory bomberman knows about */
  freeObjects(bbm->floors);
  freeObjects(bbm->blocks);
  freeObjects(bbm->boxes);
  freeSprites(bbm->sprites);
  freeGrid(bbm->grid);
}
