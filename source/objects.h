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
  It also has a pointer on void to variables
  variables is meant to be a struct (different for each object, hence the void)
*/
typedef struct {
  Coord *position;
  double sprIndex;
  double sprSpeed;
  Sprite *sprite;
  void *variables;
} Object;

/*
  'Objects' is a structure to store all the objects
  'defSprite' is the sprite by default, can be changed for each instance
  'initialisation' is a function which, if set, will be called on each new instance
  Same goes for 'update'
*/
typedef struct {
  Object **list;
  int length;
  Sprite *defSprite;
  char termChar;
  /*
    These functions are NULL by default
    The second parameter is a pointer on void
    because we don't know the 'Bomberman' structure yet
  */
  void (*initialisation)(int, void *bbmVoid);
  void (*update)(int, void *bbmVoid);
  void *bbmVoid;
} Objects;

/* Initialises the objects according to the given sprite */
Objects *initObjects(Sprite *defSprite, char termChar, void *bbmVoid);

/* Creates a new objects' instance at the coordinates x and y */
Object *newObject(Objects *, Coord *position);

/* Deletes the i-th object from the list */
void deleteObject(Objects *, int index);

/*
  Updates all the objets
  'bbmVoid' is a pointer on bbm before we know about its structure
*/
void updateObjects(Objects *);

/* Frees all the objects */
void freeObjects(Objects *);

#endif /* OBJECTS */
