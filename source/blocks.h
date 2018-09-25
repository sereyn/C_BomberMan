#ifndef BLOCKS
#define BLOCKS

#include <MLV/MLV_all.h>
#include "utils.h"

typedef struct {
	Coord *list;
	int length;
	MLV_Image *sprite;
	int size;
} Blocks;

Blocks initBlocks(MLV_Image *sprite);

void newBlock(Blocks *blocks, int x, int y);

void drawBlocks(Blocks blocks);

void freeBlocks(Blocks blocks);

#endif /* BLOCKS */
