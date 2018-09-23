#ifndef SPRITES
#define SPRITES

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	MLV_Image **list;
	int length;
} Sprites;

Sprites initSprites();

MLV_Image *newSprite(Sprites *sprites, char *fileName, int width, int height);

void freeSprites(Sprites sprites);

#endif /* SPRITES */