#ifndef SPRITES
#define SPRITES

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	MLV_Image **sprites;
	int length;
} Sprites;

Sprites initSprites();

MLV_Image *newSprite(Sprites *sprites, char *path, int width, int height);

void freeSprites(Sprites sprites);

#endif /* SPRITES */