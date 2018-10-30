#include "bombs.h"

void freeBomb(Bomb *bomb){
  free(bomb->position);
  free(bomb);
}

Bombs *initBombs(MLV_Image *sprite){
  Bombs *bombs = malloc(sizeof(Bombs));
  bombs->length = 0;
  bombs->sprite = sprite;
  bombs->list = NULL;
  return bombs;
}

void newBomb(Bombs *bombs, Coord *position){
  Bomb *bomb = malloc(sizeof(Bomb));
  bomb->position = position;
  bomb->timeLeft = 100;
  /*
    We ask for 1 more slot of memory for our list to save the new position
    Then we save that position at the end of the list and increment the length
  */
  bombs->list = realloc(bombs->list, (bombs->length+1)*sizeof(Bomb *));
  bombs->list[bombs->length++] = bomb;
}

void deleteBomb(Bombs *bombs, int index){
  int i = index;
  /* If the user asks to remove an object with a negative or too high index, something went wrong */
  if(index < 0 || index >= bombs->length){
    debug(0, "Error: cannot remove the bomb %d in a list of length %d!\n", index, bombs->length);
  }else{
    /*
      First we free the Bomb to delete
    */
    freeBomb(bombs->list[index]);
    /*
      We loop from the index-th bomb the last one
      For each iteration, we make the bomb being equal to its next one
    */
    for(; i < bombs->length-1; ++i)
      bombs->list[i] = bombs->list[i+1];
    /*
      We then have a not desired bomb at the list's end
      Also we decrement the length
    */
    bombs->list = realloc(bombs->list, (--bombs->length)*sizeof(Coord));
  }
}

void drawBombs(Bombs *bombs){
  int i = 0;
  for(; i < bombs->length; ++i)
    MLV_draw_image(bombs->sprite, bombs->list[i]->position->x, bombs->list[i]->position->y);
}

void updateBombs(Bombs *bombs){
  int i = bombs->length-1;
  for(; i >= 0; --i){
    if(bombs->list[i]->timeLeft-- == 0){
      /* Need to create flames here */
      debug(0, "Need to create flames!\n");
      deleteBomb(bombs, i);
    }
  }
  drawBombs(bombs);
}

void freeBombs(Bombs *bombs){
  /* We free the dynamically made array */
  int i = 0;
  for(; i < bombs->length; ++i)
    freeBomb(bombs->list[i]);
  free(bombs->list);
  free(bombs);
}
