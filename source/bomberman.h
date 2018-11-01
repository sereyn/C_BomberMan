#ifndef BOMBERMAN
#define BOMBERMAN

#include "objects.h"
#include "utils.h"
#include "grid.h"
#include "inputs.h"
#include "sprites.h"
#include <math.h>

/* The different states the game can be in */
typedef enum {
  sMenu, sGame, sEditor
} State;

/*
  Define the Bomberman structure
  It groups all the important stuff the game needs so that we can simply pass it as a parameter
*/
typedef struct {
  /* Sprites */
  Sprites *sprites;
  Sprite *sprBlock, *sprFloor, *sprBox, *sprSpike, *sprArrow, *sprBomb,
  *sprFlameCenter, *sprFlameXSide, *sprFlameYSide, *sprFlameRightTip,
  *sprFlameLeftTip, *sprFlameUpTip, *sprFlameDownTip;
  /* Objects */
  Objects *floors, *blocks, *boxes, *spikes, *bombs, *flames;
  /* Grid, font, inputs, state, ... */
  Grid *grid;
  MLV_Font *font;
  Inputs *inputs;
  State state;
  int closed;
  int level;
} Bomberman;

/* Initializes all the bomberman objects (floors, blocks, boxes and spikes) */
void initAllObjects(Bomberman *bbm);

/* Frees all of them */
void freeAllObjects(Bomberman *bbm);

/* Initialises a Bomberman instance */
Bomberman *initBomberman(Grid *grid);

/* Updates all the objects */
void updateAllObjects(Bomberman *bbm);

/* Changes the state of the program (menu, game or editor) */
void setState(Bomberman *bbm, State newState);

/* Manages the most important updates */
void bombermanLoop(Bomberman *bbm);

/* This function's purpose is to free the allocated memory the structure knows about */
void freeBomberman(Bomberman *bbm);

#endif /* BOMBERMAN */
