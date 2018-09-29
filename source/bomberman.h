#ifndef BOMBERMAN
#define BOMBERMAN

#include "sprites.h"
#include "objects.h"
#include "player.h"

/*
  Define the Bomberman structure
  It groups all the important stuff the game needs so that we can simply pass it as a parameter
*/
typedef struct {
  MLV_Image *sprBlock, *sprFloor, *sprBox;
  Sprites sprites;
  Objects floors;
  Objects blocks;
  Objects boxes;
  Player player;
  int gridSize;
  Coord gridDimensions;
} Bomberman;

/* Initialises a Bomberman instance */
Bomberman initBomberman(int gridSize, Coord gridDimensions);

/* Draws the whole game */
void drawAll(const Bomberman bbm);

/* This function's purpose is to free the allocated memory the structure knows about */
void freeBomberman(Bomberman bbm);

#endif /* BOMBERMAN */
