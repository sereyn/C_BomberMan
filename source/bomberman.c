#include "bomberman.h"

void initAllObjects(Bomberman *bbm){
  /* Initialises the objects according to their sprites */
  bbm->floors = initObjects(bbm->sprFloor, 'F');
  bbm->blocks = initObjects(bbm->sprBlock, 'B');
  bbm->boxes = initObjects(bbm->sprBox, 'C');
  bbm->spikes = initObjects(bbm->sprSpike, 'S');
}

void freeAllObjects(Bomberman *bbm){
  freeObjects(bbm->floors);
  freeObjects(bbm->blocks);
  freeObjects(bbm->boxes);
  freeObjects(bbm->spikes);
}

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
  bbm->aniFlameYSide = newAnimation(bbm->animations, "flame/side%d.png", spriteDims, .2, -90);
  bbm->aniFlameRightTip = newAnimation(bbm->animations, "flame/tip%d.png", spriteDims, .2, 0);
  bbm->aniFlameLeftTip = newAnimation(bbm->animations, "flame/tip%d.png", spriteDims, .2, 180);
  bbm->aniFlameUpTip = newAnimation(bbm->animations, "flame/tip%d.png", spriteDims, .2, 90);
  bbm->aniFlameDownTip = newAnimation(bbm->animations, "flame/tip%d.png", spriteDims, .2, -90);
  free(spriteDims);
  /* Inits the objects */
  initAllObjects(bbm);
  /* Loads the font */
  bbm->font = MLV_load_font("resources/fonts/font1.ttf", bbm->grid->size/2);
  /* Loads the keys */
  bbm->inputs = initInputs();
  /* Set the default state on the menu (so that the game starts by displaying the menu) */
  bbm->state = sMenu;
  /* Set the closed pseudo boolean to 0 by default */
  bbm->closed = 0;
  /* Set the level by default to play */
  bbm->level = 0;
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
  /* Prints the equivalent result into the terminal */
  printGrid(bbm->grid);
}

void setState(Bomberman *bbm, State newState){
  /* We first destroy all the objects by freeing and re initializing them */
  freeAllObjects(bbm);
  initAllObjects(bbm);
  /* Then we set its new state */
  bbm->state = newState;
}

void bombermanLoop(Bomberman *bbm){
  /* We draw everything (some content may be drawn in the subLoops though) */
  drawAll(bbm);
  /* We update the inputs and animations at every frame */
  updateInputs(bbm->inputs);
  updateAnimations(bbm->animations);
  /* Check if the user presses escape */
  if(isJustDown(bbm->inputs->escape)){
    switch(bbm->state){
      /* If it presses escape on the title screen, we quit the game */
      case sMenu:
        bbm->closed = 1;
        break;
      /* Overwise we get back to the title screen */
      default:
        setState(bbm, sMenu);
    }
  }
}

void freeBomberman(Bomberman *bbm){
  debug(0, "Free the allocated memory\n");
  /* Free all the allocated memory bomberman knows about */
  freeSprites(bbm->sprites);
  freeAnimations(bbm->animations);
  freeAllObjects(bbm);
  MLV_free_font(bbm->font);
  freeInputs(bbm->inputs);
  freeGrid(bbm->grid);
}
