#ifndef BOMBERMAN
#define BOMBERMAN

#include "sprites.h"
#include "objects.h"
#include "player.h"

typedef struct {
	MLV_Image *sprBlock, *sprFloor;
	Sprites sprites;
	Objects floors;
	Objects blocks;
	Player player;
	int gridSize;
} Bomberman;

Bomberman initBomberman();

void drawAll(const Bomberman bbm);

void freeBomberman(Bomberman bbm);

#endif /* BOMBERMAN */
