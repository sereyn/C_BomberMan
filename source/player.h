#ifndef PLAYER
#define PLAYER

#include <MLV/MLV_all.h>
#include "utils.h"

/* Temporary, might want to use the objects structure for the players as well */

typedef struct {
  Coord position;
  int speed;
} Player;

Player newPlayer();

void updatePlayer(Player *player);

#endif /* PLAYER */
