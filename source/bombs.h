#ifndef BOMBS
#define BOMBS

#include <MLV/MLV_all.h>
#include "stdlib.h"
#include "utils.h"

typedef struct {
  Coord *position;
  int timeLeft;
} Bomb;

/* Frees a Bomb */
void freeBomb(Bomb *bomb);

typedef struct {
  Bomb **list;
  int length;
  MLV_Image *sprite;
} Bombs;

/* Initialize the Bombs */
Bombs *initBombs(MLV_Image *sprite);

/* Append a Bomb in the Bombs->list */
void newBomb(Bombs *bombs, Coord *position);

/* Removes the index-th Bomb in Bombs */
void deleteBomb(Bombs *bombs, int index);

/* Renders all the Bombs */
void drawBombs(Bombs *bombs);

/* Removes the too old Bombs and draws the rest of them using drawBombs */
void updateBombs(Bombs *bombs);

/* Frees the Bombs (and every Bomb stored in it) */
void freeBombs(Bombs *bombs);

#endif /* BOMBS */
