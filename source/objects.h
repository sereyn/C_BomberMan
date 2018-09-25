#ifndef OBJECTS
#define OBJECTS

#include <MLV/MLV_all.h>
#include "utils.h"

typedef struct {
  Coord *list;
  int length;
  MLV_Image *sprite;
  Coord dimensions;
} Objects;

Objects initObjects(MLV_Image *sprite);

void newObject(Objects *objects, int x, int y);

void drawObjects(Objects objects);

void freeObjects(Objects objects);

#endif /* OBJECTS */
