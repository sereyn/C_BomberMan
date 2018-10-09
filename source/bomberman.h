#ifndef BOMBERMAN
#define BOMBERMAN

#include "sprites.h"
#include "objects.h"
#include "utils.h"
#include "grid.h"
#include "inputs.h"

/*
  Define the Bomberman structure
  It groups all the important stuff the game needs so that we can simply pass it as a parameter
*/
typedef struct {
  MLV_Image *sprBlock, *sprFloor, *sprBox, *sprSpike, *sprArrow;
  Sprites *sprites;
  Objects *floors;
  Objects *blocks;
  Objects *boxes;
  Objects *spikes;
  Grid *grid;
  MLV_Font *font;
  Inputs *inputs;
} Bomberman;

/* Initialises a Bomberman instance */
Bomberman *initBomberman(Grid *grid);

/* Draws the whole game */
void drawAll(Bomberman *bbm);

/* This function's purpose is to free the allocated memory the structure knows about */
void freeBomberman(Bomberman *bbm);

#endif /* BOMBERMAN */
