#include "objects.h"

Objects initObjects(MLV_Image *sprite, char termChar){
  Objects objects;
  objects.length = 0;
  objects.sprite = sprite;
  objects.termChar = termChar;
  /* For the dimensions, we simply get the ones of the given sprite */
  objects.dimensions.x = MLV_get_image_width(sprite);
  objects.dimensions.y = MLV_get_image_height(sprite);
  return objects;
}

void newObject(Objects *objects, int x, int y){
  /* First we create a new position which represents the new object */
  Coord position;
  position.x = x;
  position.y = y;
  /*
    We ask for 1 more slot of memory for our list to save the new position
    Then we save that position at the end of the list and increment the length
  */
  objects->list = realloc(objects->list, (objects->length+1)*sizeof(*(objects->list)));
  objects->list[objects->length++] = position;
}

void deleteObject(Objects *objects, int index){
  int i = index;
  /* If the user asks to remove an object with a negative or too high index, something went wrong */
  if(index < 0 || index >= objects->length){
    debug(0, "Error: cannot remove the object %d in a list of length %d!\n", index, objects->length);
    exit(EXIT_FAILURE);
  }
  /*
    We loop from the index-th object the last one
    For each iteration, we make the object being equal to its next one
  */
  for(; i < objects->length-1; ++i)
    objects->list[i] = objects->list[i+1];
  /*
    We then have a not desired object at the list's end so we realloc the list to free it
    Also we decrement the length
  */
  objects->list = realloc(objects->list, (--objects->length)*sizeof(*(objects->list)));
}

void drawObjects(Objects objects, TermGrid termGrid){
  /*
    We loop through all the objects to draw them all
  */
  int i = 0, x, y, termX, termY;
  for(; i < objects.length; ++i){
    x = objects.list[i].x;
    y = objects.list[i].y;
    MLV_draw_image(objects.sprite, x, y);
    termX = x/termGrid.size;
    termY = y/termGrid.size-termGrid.marginTop;
    /* We don't draw the objects in the hub */
    if(termY > -1)
      termGrid.grid[termY][termX] = objects.termChar;
  }
}

void freeObjects(Objects objects){
  /* We free the dynamically made array */
  free(objects.list);
}
