#include "bomberman.h"

Bomberman *initBomberman(Grid *grid){
  Coord *spriteDims = newCoord(grid->size, grid->size);
  Bomberman *bbm = malloc(sizeof(Bomberman));
  debug(0, "Creating bomberman\n");
  bbm->grid = grid;
  /*
    Initialises the sprites
    Then loads the sprites using newSprite
  */
  debug(0, "Loading sprites...\n");
  bbm->sprites = initSprites();
  bbm->sprBlock = newSprite(bbm->sprites, "block.png", spriteDims);
  bbm->sprFloor = newSprite(bbm->sprites, "floor.png", spriteDims);
  bbm->sprBox = newSprite(bbm->sprites, "box.png", spriteDims);
  bbm->sprSpike = newSprite(bbm->sprites, "spike.png", spriteDims);
  bbm->sprArrow = newSprite(bbm->sprites, "arrow.png", spriteDims);
  /* Loads the animations */
  bbm->animations = initAnimations();
  bbm->aniBomb = newAnimation(bbm->animations, "bomb/bomb%d.png", spriteDims, .03, 0);
  bbm->aniFlameCenter = newAnimation(bbm->animations, "flame/center%d.png", spriteDims, .2, 0);
  bbm->aniFlameXSide = newAnimation(bbm->animations, "flame/side%d.png", spriteDims, .2, 0);
  bbm->aniFlameXTip = newAnimation(bbm->animations, "flame/tip%d.png", spriteDims, .2, 0);
  bbm->aniFlameYSide = newAnimation(bbm->animations, "flame/side%d.png", spriteDims, .2, -90);
  bbm->aniFlameYTip = newAnimation(bbm->animations, "flame/tip%d.png", spriteDims, .2, -90);
  free(spriteDims);
  /* Initialises the objects according to their sprites */
  bbm->floors = initObjects(bbm->sprFloor, 'F');
  bbm->blocks = initObjects(bbm->sprBlock, 'B');
  bbm->boxes = initObjects(bbm->sprBox, 'C');
  bbm->spikes = initObjects(bbm->sprSpike, 'S');
  /* Loads the font */
  bbm->font = MLV_load_font("resources/fonts/font1.ttf", bbm->grid->size/2);
  /* Loads the keys */
  bbm->inputs = initInputs();
  /* Set the default state on the menu (so that the game starts by displaying the menu) */
  bbm->state = sMenu;
  return bbm;
}

void drawAll(Bomberman *bbm){
  /* Fills the grid with zeros */
  resetGrid(bbm->grid);
  /* Draws all the objects (which will also prepare the grid) */
  drawObjects(bbm->floors, bbm->grid);
  drawObjects(bbm->blocks, bbm->grid);
  drawObjects(bbm->boxes, bbm->grid);
  drawObjects(bbm->spikes, bbm->grid);
  /* Temporarily draw animation for test purposes */
  /*drawAnimation(bbm->aniBomb, 0, 0);
  drawAnimation(bbm->aniFlameCenter, bbm->grid->size, 0);
  drawAnimation(bbm->aniFlameXSide, 2*bbm->grid->size, 0);
  drawAnimation(bbm->aniFlameXTip, 3*bbm->grid->size, 0);
  drawAnimation(bbm->aniFlameYSide, bbm->grid->size, bbm->grid->size);
  drawAnimation(bbm->aniFlameYTip, bbm->grid->size, 2*bbm->grid->size);*/
  /* Prints the equivalent result into the terminal */
  printGrid(bbm->grid);
}

void freeBomberman(Bomberman *bbm){
  debug(0, "Free the allocated memory\n");
  /* Free all the allocated memory bomberman knows about */
  freeSprites(bbm->sprites);
  freeAnimations(bbm->animations);
  freeObjects(bbm->floors);
  freeObjects(bbm->blocks);
  freeObjects(bbm->boxes);
  freeObjects(bbm->spikes);
  MLV_free_font(bbm->font);
  freeInputs(bbm->inputs);
  freeGrid(bbm->grid);
}
