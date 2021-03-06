#ifndef PLAYER
#define PLAYER

#include "../objects.h"
#include "../sprites.h"
#include "../inputs.h"
#include "bomb.h"
#include "flame.h"
#include <math.h>

typedef struct {
  int flameLength;
  double speed;
  int bombThrown; /* How many bomb have been thrown */
  int bombMax; /* Maximum of bomb that can be thrown at once */
  Input *up, *left, *down, *right, *action;
  int number;
  Sprite *sprites[4];
  int dead;
  int score;
} PlayerVars;

void initPlayer(int index, void *bbmVoid);

void updatePlayer(int index, void *bbmVoid);

#endif /* PLAYER */
