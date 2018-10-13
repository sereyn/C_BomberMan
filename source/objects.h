#ifndef OBJECTS
#define OBJECTS

#include <MLV/MLV_all.h>
#include "stdlib.h"
#include "utils.h"
#include "grid.h"

/*
  Objects is a structure to represent object-like concepts
  i.e. blocks, bricks, players, ...
  An object has coordinates
  Every object has in common the sprite
*/
typedef struct {
  Coord **list;
  int length;
  MLV_Image *sprite;
  char termChar;
} Objects;

/* Initialises the objects according to the given sprite */
Objects *initObjects(MLV_Image *sprite, char termChar);

/* Creates a new objects' instance at the coordinates x and y */
void newObject(Objects *objects, Coord *position);

/* Deletes the i-th object from the list */
void deleteObject(Objects *objects, int index);

/* Draws all the objets */
void drawObjects(Objects *objects, Grid *grid);

/* Frees all the objects */
void freeObjects(Objects *objects);

#endif /* OBJECTS */
