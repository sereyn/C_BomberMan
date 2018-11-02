#include "bomberman.h"

void initAllSprites(Bomberman *bbm){
  int i;
  char path[50];
  Coord *spriteDims = newCoord(bbm->grid->size, bbm->grid->size);
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
  /* Players */
  for(i = 0; i < 4; ++i){
    sprintf(path, "%s%d%s", "players/", i, "/down%d.png");
    bbm->sprPlayerDown[i] = newSprite(bbm->sprites, path, spriteDims, 0);
    sprintf(path, "%s%d%s", "players/", i, "/up%d.png");
    bbm->sprPlayerUp[i] = newSprite(bbm->sprites, path, spriteDims, 0);
    sprintf(path, "%s%d%s", "players/", i, "/left%d.png");
    bbm->sprPlayerLeft[i] = newSprite(bbm->sprites, path, spriteDims, 0);
    sprintf(path, "%s%d%s", "players/", i, "/right%d.png");
    bbm->sprPlayerRight[i] = newSprite(bbm->sprites, path, spriteDims, 0);
  }free(spriteDims);
}

void initAllObjects(Bomberman *bbm){
  /*
    Initialises the objects according to their sprites
    Also we give the optional init and update functions
  */
  bbm->floors = initObjects(bbm->sprFloor, 'F', bbm);
  bbm->blocks = initObjects(bbm->sprBlock, 'B', bbm);
  bbm->boxes = initObjects(bbm->sprBox, 'C', bbm);
  bbm->spikes = initObjects(bbm->sprSpike, 'S', bbm);
  bbm->bombs = initObjects(bbm->sprBomb, 'E', bbm);
  bbm->bombs->initialisation = &initBomb;
  bbm->bombs->update = &updateBomb;
  bbm->flames = initObjects(bbm->sprFlameCenter, 'G', bbm);
  bbm->flames->initialisation = &initFlame;
  bbm->flames->update = &updateFlame;
  bbm->players = initObjects(bbm->sprPlayerDown[0], 'P', bbm);
  bbm->players->initialisation = &initPlayer;
  bbm->players->update = &updatePlayer;
}

void freeAllObjects(Bomberman *bbm){
  freeObjects(bbm->floors);
  freeObjects(bbm->blocks);
  freeObjects(bbm->boxes);
  freeObjects(bbm->spikes);
  freeObjects(bbm->bombs);
  freeObjects(bbm->flames);
  freeObjects(bbm->players);
}

Bomberman *initBomberman(Grid *grid){
  Bomberman *bbm = malloc(sizeof(Bomberman));
  debug(0, "Creating bomberman\n");
  bbm->grid = grid;
  initAllSprites(bbm);
  initAllObjects(bbm);
  bbm->font = MLV_load_font("resources/fonts/font1.ttf", bbm->grid->size/2);
  bbm->inputs = initInputs();
  bbm->state = sMenu;
  bbm->closed = 0;
  bbm->level = 0;
  return bbm;
}

void setState(Bomberman *bbm, State newState){
  /* We first destroy all the objects by freeing and re initializing them */
  freeAllObjects(bbm);
  initAllObjects(bbm);
  /* Then we set its new state */
  bbm->state = newState;
}

void bombermanLoop(Bomberman *bbm){
  /* Fills the grid with zeros */
  resetGrid(bbm->grid);
  /* We update all the objects and the inputs */
  updateObjects(bbm->floors);
  updateObjects(bbm->blocks);
  updateObjects(bbm->spikes);
  updateObjects(bbm->bombs);
  updateObjects(bbm->flames);
  updateObjects(bbm->boxes);
  updateObjects(bbm->players);
  updateInputs(bbm->inputs);
  /* Prints the equivalent result into the terminal */
  printGrid(bbm->grid);
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
