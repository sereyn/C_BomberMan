#ifndef BOMB
#define BOMB

#include "../objects.h"
#include "../sprites.h"
#include "player.h"
#include <math.h>

typedef struct {
  int player;
} BombVars;

void initBomb(int index, void *bbmVoid);

void updateBomb(int index, void *bbmVoid);

#endif /* BOMB */
