#ifndef OBJECTS
#define OBJECTS

#include <MLV/MLV_all.h>
#include "stdlib.h"
#include "utils.h"
#include "grid.h"
#include "sprites.h"

/*
  Object is a structure to represent object-like concepts
  i.e. blocks, bricks, players, ...
  An object has coordinates, sprIndex, ...
*/
typedef struct {
  Coord *position;
  double sprIndex;
  double sprSpeed;
  Sprite *sprite;
} Object;

/* Frees an object */
void freeObject(Object *object);

/*
  Objects is a structure to store all the objects
  defSprite is the sprite by default, can be changed for each instance
*/
typedef struct {
  Object **list;
  int length;
  Sprite *defSprite;
  char termChar;
} Objects;

/* Initialises the objects according to the given sprite */
Objects *initObjects(Sprite *defSprite, char termChar);

/* Creates a new objects' instance at the coordinates x and y */
Object *newObject(Objects *objects, Coord *position);

/* Deletes the i-th object from the list */
void deleteObject(Objects *objects, int index);

/* Updates all the objets */
void updateObjects(Objects *objects, Grid *grid);

/* Frees all the objects */
void freeObjects(Objects *objects);

#endif /* OBJECTS */
