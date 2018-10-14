#ifndef SPRITES
#define SPRITES

#include <MLV/MLV_all.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

/*
  We define a Sprites structure
  It's purpose is to save all the MLV_Image in an array so that we can easily free them all at the end
*/

typedef struct {
  MLV_Image **list;
  int length;
} Sprites;

Sprites *initSprites(void);

/* Creates a new sprite from the image file 'fileName' and resize it */
MLV_Image *newSprite(Sprites *sprites, char *fileName, Coord *dimensions);

/* Frees the sprites (the whole purpose) */
void freeSprites(Sprites *sprites);

#endif /* SPRITES */