#include "objects.h"
#include "bomberman.h"

void freeObject(Object *object){
  free(object->position);
  free(object);
}

Objects *initObjects(Sprite *defSprite, char termChar, void *bbmVoid){
  Objects *objects = malloc(sizeof(Objects));
  objects->length = 0;
  objects->defSprite = defSprite;
  objects->termChar = termChar;
  objects->list = NULL;
  objects->initialisation = NULL;
  objects->update = NULL;
  objects->bbmVoid = bbmVoid;
  return objects;
}

Object *newObject(Objects *objects, Coord *position){
  /* We create the new object */
  Object *newObj = malloc(sizeof(Object));
  newObj->sprIndex = 0;
  newObj->sprSpeed = 1;
  newObj->position = position;
  newObj->sprite = objects->defSprite;
  newObj->variables = NULL;
  /*
    We ask for 1 more slot of memory for our list to save the new position
    Then we save that position at the end of the list and increment the length
  */
  objects->list = realloc(objects->list, (objects->length+1)*sizeof(Coord *));
  objects->list[objects->length++] = newObj;
  /* Now that everything is ready, we call the init function if it exists */
  if(objects->initialisation)
    (*(objects->initialisation))(objects->length-1, objects->bbmVoid);
  return newObj;
}

void deleteObject(Objects *objects, int index){
  int i = index;
  /* If the user asks to remove an object with a negative or too high index, something went wrong */
  if(index < 0 || index >= objects->length){
    debug(0, "Error: cannot remove the object %d in a list of length %d!\n", index, objects->length);
  }else{
    /*
      First we free the object to delete
    */
    freeObject(objects->list[index]);
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

void updateObjects(Objects *objects){
  /* Now that we know about the 'Bomberman' structure, we can convert it */
  Bomberman *bbm = objects->bbmVoid;
  /* We loop through all the objects to update them all */
  int i, x, y, termX, termY;
  /* The current object we're dealing with */
  Object *curObj;
  for(i = objects->length-1; i >= 0; --i){
    curObj = objects->list[i];
    x = curObj->position->x;
    y = curObj->position->y;
    /* We increase the sprite index according to the speed and the maximum index */
    curObj->sprIndex += curObj->sprSpeed;
    while(curObj->sprIndex >= curObj->sprite->length)
      curObj->sprIndex -= (double)objects->list[i]->sprite->length;
    /* Normal (window) rendering */
    drawSprite(curObj->sprite, x, y, (int)curObj->sprIndex);
    /* Terminal rendering */
    termX = x/bbm->grid->size;
    termY = y/bbm->grid->size-bbm->grid->marginTop;
    /* We don't print the objects in the hub (too high) in the terminal */
    if(termX > -1 && termX < bbm->grid->dimensions->x
    && termY > -1 && termY < bbm->grid->dimensions->y)
      bbm->grid->grid[termY][termX] = objects->termChar;
    /* If the object has an update function, we execute it */    
    if(objects->update)
      (*(objects->update))(i, bbm);
  }
}

void freeObjects(Objects *objects){
  /* We free the dynamically made array */
  int i = 0;
  for(; i < objects->length; ++i)
    freeObject(objects->list[i]);
  free(objects->list);
  free(objects);
}
