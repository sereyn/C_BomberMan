#include "bomb.h"
#include "../bomberman.h"

void initBomb(int index, void *bbmVoid){
  Bomberman *bbm = bbmVoid;
  Object *bomb = bbm->bombs->list[index];
  BombVars *bombVars = malloc(sizeof(BombVars));
  bombVars->player = 0;
  bomb->variables = bombVars;
  bomb->sprSpeed = .03;
}

void updateBomb(int index, void *bbmVoid){
  Bomberman *bbm = bbmVoid;
  int x, y, x2, y2, i, j, k;
  Object *flame, *block, *box, *bomb = bbm->bombs->list[index];
  BombVars *bombVars = bomb->variables;
  PlayerVars *playerVars = bbm->players->list[bombVars->player]->variables;
  FlameVars *flameVars;
  int flameLength = playerVars->flameLength;
  /*
    flameDestroyed represents the directions in which the flame encountered some blocks
    We fill it with zeroes
  */
  int flameDestroyed[4] = {0};
  /* We make these 2 arrays for simplifying a coming for loop */
  Sprite *sprFlameSide[2], *sprFlameTip[4];
  sprFlameSide[0] = bbm->sprFlameXSide;
  sprFlameSide[1] = bbm->sprFlameYSide;
  sprFlameTip[0] = bbm->sprFlameRightTip;
  sprFlameTip[1] = bbm->sprFlameDownTip;
  sprFlameTip[2] = bbm->sprFlameLeftTip;
  sprFlameTip[3] = bbm->sprFlameUpTip;
  if((int)bomb->sprIndex == bomb->sprite->length-1){
    x = bomb->position->x;
    y = bomb->position->y;
    /*
      We create the flames
      We have a double for loop: one for the distance from the center and the other for the direction
    */
    for(i = 0; i <= flameLength; ++i){
      for(j = 0; j < 4; ++j){
        /* We check if the flame has been destroyed already */
        if(flameDestroyed[j])
          continue;
        /* 1.57 is an approximation of PI/2 */
        x2 = x+bbm->grid->size*i*round(cos((double)j*1.57));
        y2 = y+bbm->grid->size*i*round(sin((double)j*1.57));
        /* We check if that place is taken by a block */
        for(k = 0; k < bbm->blocks->length; ++k){
          block = bbm->blocks->list[k];
          if(block->position->x == x2 && block->position->y == y2){
            flameDestroyed[j] = 1;
            break;
          }
        }
        /* We repeat the same process but with boxes, and if a box is in the place we delete it */
        for(k = bbm->boxes->length-1; k >= 0; --k){
          box = bbm->boxes->list[k];
          if(box->position->x == x2 && box->position->y == y2){
            flameDestroyed[j] = 1;
            deleteObject(bbm->boxes->list[k]);
            /* We create a flame where the box got destroyed */
            flame = newObject(bbm->flames, newCoord(x2, y2));
            flame->sprite = sprFlameTip[j];
            flameVars = flame->variables;
            flameVars->player = bombVars->player;
            /* We add a score of 5 to the player who destroyed the box */
            playerVars->score += 5;
            break;
          }
        }
        /* Again, we check if the flame has been destroyed */
        if(flameDestroyed[j])
          continue;
        /* Finally we can create the flame */
        flame = newObject(bbm->flames, newCoord(x2, y2));
        flameVars = flame->variables;
        flameVars->player = bombVars->player;
        /* If i is 0, then we're at the center and we don't need to loop through all the directions */
        if(i == 0)
          break;
        /* If i is flameLength, we're on the tip of the flames */
        else if(i == flameLength)
          flame->sprite = sprFlameTip[j];
        /* Otherwise we're on a side */
        else
          flame->sprite = sprFlameSide[j%2];
      }
    }
    playerVars->bombThrown--;
    deleteObject(bomb);
  }
}
