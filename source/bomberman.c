#include "bomberman.h"

void initAllObjects(Bomberman *bbm){
  /* Initialises the objects according to their sprites */
  bbm->floors = initObjects(bbm->sprFloor, 'F');
  bbm->blocks = initObjects(bbm->sprBlock, 'B');
  bbm->boxes = initObjects(bbm->sprBox, 'C');
  bbm->spikes = initObjects(bbm->sprSpike, 'S');
  bbm->bombs = initObjects(bbm->sprBomb, 'E');
  bbm->flames = initObjects(bbm->sprFlameCenter, 'G');
}

void freeAllObjects(Bomberman *bbm){
  freeObjects(bbm->floors);
  freeObjects(bbm->blocks);
  freeObjects(bbm->boxes);
  freeObjects(bbm->spikes);
  freeObjects(bbm->bombs);
  freeObjects(bbm->flames);
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
  int i, j, k, l, size = bbm->grid->size;
  int x, y, x2, y2;
  int flameDestroyed[4];
  int flameLength = 2;
  Object *flame;
  /* We make these 2 arrays for simplifying a coming for loop */
  Sprite *sprFlameSide[2], *sprFlameTip[4];
  sprFlameSide[0] = bbm->sprFlameXSide;
  sprFlameSide[1] = bbm->sprFlameYSide;
  sprFlameTip[0] = bbm->sprFlameRightTip;
  sprFlameTip[1] = bbm->sprFlameDownTip;
  sprFlameTip[2] = bbm->sprFlameLeftTip;
  sprFlameTip[3] = bbm->sprFlameUpTip;
  /* Fills the grid with zeros */
  resetGrid(bbm->grid);
  /* Update the objects (draws them, prepare the terminal grid to print them, ...) */
  updateObjects(bbm->floors, bbm->grid);
  updateObjects(bbm->blocks, bbm->grid);
  updateObjects(bbm->spikes, bbm->grid);
  /*
    For the bombs, we also check if the animation is over
    If that's the case we remove it and create the flames
    We do this loop backward to avoid skipping a bomb to remove
  */
  updateObjects(bbm->bombs, bbm->grid);
  for(i = bbm->bombs->length-1; i >= 0; --i){
    if((int)bbm->bombs->list[i]->sprIndex == bbm->bombs->defSprite->length-1){
      x = bbm->bombs->list[i]->position->x;
      y = bbm->bombs->list[i]->position->y;
      /*
        flameDestroyed represents the directions in which the flame encountered some blocks
        We fill it with zeroes
      */
      for(j = 0; j < 4; ++j)
        flameDestroyed[j] = 0;
      /*
        We create the flames
        We have a double for loop: one for the distance from the center and the other for the direction
      */
      for(k = 0; k <= flameLength; ++k){
        for(j = 0; j < 4; ++j){
          /* We check if the flame has been destroyed already */
          if(flameDestroyed[j])
            continue;
          /* 1.57 is an approximation of PI/2 */
          x2 = x+size*k*round(cos((double)j*1.57));
          y2 = y+size*k*round(sin((double)j*1.57));
          /* We check if that place is taken by a block */
          for(l = 0; l < bbm->blocks->length; ++l){
            if(bbm->blocks->list[l]->position->x == x2 && bbm->blocks->list[l]->position->y == y2){
              flameDestroyed[j] = 1;
              break;
            }
          }
          /* We repeat the same process but with boxes, and if a box is in the place we delete it */
          for(l = bbm->boxes->length-1; l >= 0; --l){
            if(bbm->boxes->list[l]->position->x == x2 && bbm->boxes->list[l]->position->y == y2){
              flameDestroyed[j] = 1;
              deleteObject(bbm->boxes, l);
              /* We create a flame where the box got destroyed */
              flame = newObject(bbm->flames, newCoord(x2, y2));
              flame->sprSpeed = .3;
              flame->sprite = sprFlameTip[j];
              break;
            }
          }
          /* Again, we check if the flame has been destroyed */
          if(flameDestroyed[j])
            continue;
          /* Finally we can create the flame */
          flame = newObject(bbm->flames, newCoord(x2, y2));
          flame->sprSpeed = .3;
          /* If k is 0, then we're at the center and we don't need to loop through all the directions */
          if(k == 0)
            break;
          /* If k is flameLength, we're on the tip of the flames */
          if(k == flameLength)
            flame->sprite = sprFlameTip[j];
          /* Otherwise we're on a side */
          else
            flame->sprite = sprFlameSide[j%2];
        }
      }
      deleteObject(bbm->bombs, i);
    }
  }
  /* Same goes for flames: destroyed once the sprite is over */
  updateObjects(bbm->flames, bbm->grid);
  for(i = bbm->flames->length-1; i >= 0; --i){
    if((int)bbm->flames->list[i]->sprIndex == bbm->flames->list[i]->sprite->length-1)
      deleteObject(bbm->flames, i);
  }
  updateObjects(bbm->boxes, bbm->grid);
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
