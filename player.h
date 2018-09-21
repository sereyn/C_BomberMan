#ifndef PLAYER
#define PLAYER

#include <MLV/MLV_all.h>
#include "window.h"

typedef struct {
  /* pixel position */
  int x;
  int y;
  /* speed in px per sec */
  int speed;
} Player;

Player newPlayer();

void updatePlayer(Player* player);

#endif /* PLAYER */
