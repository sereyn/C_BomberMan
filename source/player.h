#ifndef PLAYER
#define PLAYER

#include <MLV/MLV_all.h>
#include "utils.h"

typedef struct {
  Coord position;
  int speed;
} Player;

Player newPlayer();

void updatePlayer(Player *player);

#endif /* PLAYER */
