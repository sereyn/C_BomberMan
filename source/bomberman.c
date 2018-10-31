#include "bomberman.h"

void initAllObjects(Bomberman *bbm){
  /* Initialises the objects according to their sprites */
  bbm->floors = initObjects(bbm->sprFloor, 'F');
  bbm->blocks = initObjects(bbm->sprBlock, 'B');
  bbm->boxes = initObjects(bbm->sprBox, 'C');
  bbm->spikes = initObjects(bbm->sprSpike, 'S');
  bbm->bombs = initObjects(bbm->sprBomb, 'E');
}

void freeAllObjects(Bomberman *bbm){
  freeObjects(bbm->floors);
  freeObjects(bbm->blocks);
  freeObjects(bbm->boxes);
  freeObjects(bbm->spikes);
  freeObjects(bbm->bombs);
}

Bomberman *initBomberman(Grid *grid){
  Coord *spriteDims = newCoord(grid->size, grid->size);
  Bomberman *bbm = malloc(sizeof(Bomberman));
  debug(0, "Creating bomberman\n");
  bbm->grid = grid;
  /* Loads the sprites */
  debug(0, "Loading sprites...\n");
  bbm->sprites = initSprites();
  bbm->sprBlock = newSprite(bbm->sprites, "block%d.png", spriteDims, 0);
  bbm->sprFloor = newSprite(bbm->sprites, "floor%d.png", spriteDims, 0);
  bbm->sprBox = newSprite(bbm->sprites, "box%d.png", spriteDims, 0);
  bbm->sprSpike = newSprite(bbm->sprites, "spike%d.png", spriteDims, 0);
  bbm->sprArrow = newSprite(bbm->sprites, "arrow%d.png", spriteDims, 0);
  bbm->sprBomb = newSprite(bbm->sprites, "bomb/bomb%d.png", spriteDims, 0);
  bbm->sprFlameCenter = newSprite(bbm->sprites, "flame/center%d.png", spriteDims, 0);
  bbm->sprFlameXSide = newSprite(bbm->sprites, "flame/side%d.png", spriteDims, 0);
  bbm->sprFlameYSide = newSprite(bbm->sprites, "flame/side%d.png", spriteDims, -90);
  bbm->sprFlameRightTip = newSprite(bbm->sprites, "flame/tip%d.png", spriteDims, 0);
  bbm->sprFlameLeftTip = newSprite(bbm->sprites, "flame/tip%d.png", spriteDims, 180);
  bbm->sprFlameUpTip = newSprite(bbm->sprites, "flame/tip%d.png", spriteDims, 90);
  bbm->sprFlameDownTip = newSprite(bbm->sprites, "flame/tip%d.png", spriteDims, -90);
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

void updateAllObjects(Bomberman *bbm){
  int i;
  /* Fills the grid with zeros */
  resetGrid(bbm->grid);
  /* Draws all the objects (which will also prepare the grid) */
  updateObjects(bbm->floors, bbm->grid);
  updateObjects(bbm->blocks, bbm->grid);
  updateObjects(bbm->boxes, bbm->grid);
  updateObjects(bbm->spikes, bbm->grid);
  /*
    For the bombs, we also check if the animation is over and, if that's the case we remove it
    We do this loop backward to avoid skipping a bomb to remove
  */
  updateObjects(bbm->bombs, bbm->grid);
  for(i = bbm->bombs->length-1; i >= 0; --i){
    if((int)bbm->bombs->list[i]->sprIndex == bbm->bombs->sprite->length-1){
      /* Need to create flames here and now */
      debug(0, "Need to create flames now!\n");
      deleteObject(bbm->bombs, i);
    }
  }
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
  /* We update all the objects and the inputs */
  updateAllObjects(bbm);
  updateInputs(bbm->inputs);
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
  freeAllObjects(bbm);
  MLV_free_font(bbm->font);
  freeInputs(bbm->inputs);
  freeGrid(bbm->grid);
}
