#include "objects.h"

Objects *initObjects(MLV_Image *sprite, char termChar){
  Objects *objects = malloc(sizeof(Objects));
  objects->length = 0;
  objects->sprite = sprite;
  objects->termChar = termChar;
  objects->list = NULL;
  return objects;
}

void newObject(Objects *objects, Coord *position){
  /*
    We ask for 1 more slot of memory for our list to save the new position
    Then we save that position at the end of the list and increment the length
  */
  objects->list = realloc(objects->list, (objects->length+1)*sizeof(Coord *));
  objects->list[objects->length++] = position;
}

void deleteObject(Objects *objects, int index){
  int i = index;
  /* If the user asks to remove an object with a negative or too high index, something went wrong */
  if(index < 0 || index >= objects->length){
    debug(0, "Error: cannot remove the object %d in a list of length %d!\n", index, objects->length);
  }else{
    /*
      First we free the Coord to delete
    */
    free(objects->list[index]);
    /*
      We loop from the index-th object the last one
      For each iteration, we make the object being equal to its next one
    */
    for(; i < objects->length-1; ++i)
      objects->list[i] = objects->list[i+1];
    /*
      We then have a not desired object at the list's end
      Also we decrement the length
    */
    objects->list = realloc(objects->list, (--objects->length)*sizeof(Coord));
  }
}

void drawObjects(Objects *objects, Grid *grid){
  /*
    We loop through all the objects to draw them all
  */
  int i = 0, x, y, termX, termY;
  for(; i < objects->length; ++i){
    x = objects->list[i]->x;
    y = objects->list[i]->y;
    MLV_draw_image(objects->sprite, x, y);
    termX = x/grid->size;
    termY = y/grid->size-grid->marginTop;
    /* We don't print the objects in the hub in the terminal*/
    if(termY > -1)
      grid->grid[termY][termX] = objects->termChar;
  }
}

void freeObjects(Objects *objects){
  /* We free the dynamically made array */
  int i = 0;
  for(; i < objects->length; ++i)
    free(objects->list[i]);
  free(objects->list);
  free(objects);
}
