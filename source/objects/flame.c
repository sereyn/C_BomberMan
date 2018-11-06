#include "flame.h"
#include "../bomberman.h"

void initFlame(int index, void *bbmVoid){
  Bomberman *bbm = bbmVoid;
  Object *flame = bbm->flames->list[index];
  flame->sprSpeed = .3;
}

void updateFlame(int index, void *bbmVoid){
  /* We delete the flame when it's animation is over */
  Bomberman *bbm = bbmVoid;
  Object *flame = bbm->flames->list[index];
  if((int)flame->sprIndex == flame->sprite->length-1)
    deleteObject(bbm->flames, index);
}
