#ifndef BOMBERMAN
#define BOMBERMAN

#include "utils.h"
#include "grid.h"
#include "sprites.h"
#include "objects.h"
#include "objectsProps.h"
#include "inputs.h"

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
  Objects *floors, *blocks, *boxes, *spikes, *bombs, *flames, *players;
  /* Grid, font, inputs, state, ... */
  Grid *grid;
  MLV_Font *font;
  Inputs *inputs;
  State state;
  int closed;
  int level;
} Bomberman;

/* Initialises a Bomberman instance */
Bomberman *initBomberman(Grid *);

/* Changes the state of the program (menu, game or editor) */
void setState(Bomberman *, State);

/* Manages the most important updates */
void bombermanLoop(Bomberman *);

/* This function's purpose is to free the allocated memory the structure knows about */
void freeBomberman(Bomberman *);

#endif /* BOMBERMAN */
