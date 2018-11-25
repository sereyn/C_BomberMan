#include "bonus.h"
#include "../bomberman.h"

void initBonus(int index, void *bbmVoid){
  /* We randomly choose between a bomb bonus, a flame bonus, or a speed bonus */
  Bomberman *bbm = bbmVoid;
  Object *bonus = bbm->bonus->list[index];
  BonusVars *bonusVars = malloc(sizeof(BonusVars));
  switch(rand()%3){
    case 0:
      bonusVars->bonusType = bBomb;
      bonus->sprite = bbm->sprBonusBomb;
      break;
    case 1:
      bonusVars->bonusType = bFlame;
      bonus->sprite = bbm->sprBonusFlame;
      break;
    case 2:
      bonusVars->bonusType = bSpeed;
      bonus->sprite = bbm->sprBonusSpeed;
      break;
  }
  bonus->variables = bonusVars;
}

/* Returns -1 if no collision, or else, returns the player number */
int collisionWithPlayer(int index, Bomberman *bbm){
  int i = 0;
  Object *bonus = bbm->bonus->list[index];
  Coord *sprDims = bbm->bonus->defSprite->dimensions;
  int x1 = bonus->position->x, y1 = bonus->position->y;
  int x2 = x1+sprDims->x, y2 = y1+sprDims->y;
  int px1, py1, px2, py2;
  int xColl;
  int yColl;
  Object *player;
  for(; i < bbm->numberPlayers; ++i){
    player = bbm->players->list[i];
    px1 = player->position->x, py1 = player->position->y;
    px2 = px1+bbm->grid->size, py2 = py1+bbm->grid->size;
    xColl = x1 < px2 && px1 < x2;
    yColl = y1 < py2 && py1 < y2;
    if(xColl && yColl)
      return i;
  }
  return -1;
}

void updateBonus(int index, void *bbmVoid){
  Bomberman *bbm = bbmVoid;
  Object *bonus = bbm->bonus->list[index];
  BonusVars *bonusVars = bonus->variables;
  PlayerVars *playerVars;
  int collision = collisionWithPlayer(index, bbm);
  if(collision > -1){
    playerVars = bbm->players->list[collision]->variables;
    switch(bonusVars->bonusType){
      case bBomb:
        playerVars->bombMax++;
        break;
      case bFlame:
        playerVars->flameLength++;
        break;
      case bSpeed:
        playerVars->speed += .5;
        break;
    }
    playerVars->score -= 10;
    deleteObject(bonus);
  }
}
