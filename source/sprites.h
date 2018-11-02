#ifndef SPRITES
#define SPRITES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <MLV/MLV_all.h>
#include "utils.h"

/* The basic Sprite structure (a list of images) */
typedef struct {
  MLV_Image **list;
  int length;
} Sprite;

/* Draws the sprite to the screen at the coordinates (x, y) */
void drawSprite(Sprite *, int x, int y, int index);

/* The Sprites structure's purpose is to get an exhaustive list of all the Sprite structures */
typedef struct {
  Sprite **list;
  int length;
} Sprites;

/* Initializes a Sprites, now ready to contain Sprite structures */
Sprites *initSprites(void);

/*
  When creating a new Sprite, you need to provide the string of the file pattern
  (i.e. "bomb%d.png" if your sprite is "bomb0.png", "bomb1.png", ..., "bomb5.png")
*/
Sprite *newSprite(Sprites *, char *filePattern, Coord *dimensions, double rotation);

/* Frees all the sprites */
void freeSprites(Sprites *);

#endif /* SPRITES */
