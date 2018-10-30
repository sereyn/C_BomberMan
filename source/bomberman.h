#ifndef BOMBERMAN
#define BOMBERMAN

#include "sprites.h"
#include "objects.h"
#include "utils.h"
#include "grid.h"
#include "inputs.h"
#include "animations.h"
#include "bombs.h"

typedef enum {
  sMenu, sGame, sEditor
} State;

/*
  Define the Bomberman structure
  It groups all the important stuff the game needs so that we can simply pass it as a parameter
*/
typedef struct {
  MLV_Image *sprBlock, *sprFloor, *sprBox, *sprSpike, *sprArrow, *sprBomb;
  Animation *aniFlameCenter, *aniFlameXSide, *aniFlameYSide,
  *aniFlameRightTip, *aniFlameLeftTip, *aniFlameUpTip, *aniFlameDownTip;
  Sprites *sprites;
  Animations *animations;
  Objects *floors;
  Objects *blocks;
  Objects *boxes;
  Objects *spikes;
  Bombs *bombs;
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

/* Draws the whole game */
void drawAll(Bomberman *bbm);

/* Changes the state of the program (menu, game or editor) */
void setState(Bomberman *bbm, State newState);

/* Manages the most important updates */
void bombermanLoop(Bomberman *bbm);

/* This function's purpose is to free the allocated memory the structure knows about */
void freeBomberman(Bomberman *bbm);

#endif /* BOMBERMAN */
