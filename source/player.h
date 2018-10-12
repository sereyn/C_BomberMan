#ifndef PLAYER
#define PLAYER

#include <MLV/MLV_all.h>
#include "utils.h"
#include "bomberman.h"
#include "inputs.h"

/* The player structure */
typedef struct {
  Coord *position;
  int speed;
  MLV_Color color;
  int size;
  Input *up, *left, *down, *right;
} Player;

/* Creates a new player */
Player *newPlayer(Bomberman *bbm, int number);

/* Moves and draws the player */
void updatePlayer(Player *player);

/* Frees the player memory */
void freePlayer(Player *player);

#endif /* PLAYER */
