#ifndef BOMBERMAN
#define BOMBERMAN

#include "utils.h"
#include "grid.h"
#include "sprites.h"
#include "objects.h"
#include "inputs.h"
#include <stdlib.h>

#include "objects/player.h"
#include "objects/bomb.h"
#include "objects/flame.h"
#include "objects/bonus.h"

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
  *sprFlameLeftTip, *sprFlameUpTip, *sprFlameDownTip, *sprBonusFlame, *sprBonusBomb, *sprBonusSpeed,
  *sprPlayerDown[4], *sprPlayerUp[4], *sprPlayerLeft[4], *sprPlayerRight[4], *sprPlayerDead;
  /* Objects */
  Objects *floors, *blocks, *boxes, *spikes, *bombs, *flames, *players, *bonus;
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
