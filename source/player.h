#ifndef PLAYER
#define PLAYER

#include <MLV/MLV_all.h>
#include "utils.h"
#include "bomberman.h"
#include "inputs.h"
#include "objects.h"

/* The player structure */
typedef struct {
  Coord *position;
  int speed;
  MLV_Color color;
  int size;
  Input *up, *left, *down, *right, *action;
} Player;

/* Creates a new player */
Player *newPlayer(Bomberman *bbm, int number);

/*
  Returns if whether or not a player is colliding with an object at the 'position' coordinates
  (blocks, boxes or spikes)
*/
int playerCollides(Player *player, int x, int y, Bomberman *bbm);

/* Moves the player */
void movePlayer(Player *player, Bomberman *bbm);

/* Manages the attacks of the player */
void attackPlayer(Player *player, Bomberman *bbm);

/* Draws the player */
void drawPlayer(Player *player);

/* Moves and draws the player, has to be called at every frame */
void updatePlayer(Player *player, Bomberman *bbm);

/* Frees the player memory */
void freePlayer(Player *player);

#endif /* PLAYER */
