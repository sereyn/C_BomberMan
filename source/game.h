#ifndef GAME
#define GAME

#include "utils.h"
#include "files.h"
#include "objects.h"
#include "player.h"

typedef struct {
  Player *players[4];
} Game;

/* Inits the game */
Game *initGame(Bomberman *bbm);

/* Has to be executed in a game loop: main function of the game */
void gameLoop(Game *game, Bomberman *bbm);

/*
  Frees the game
  Has to be a pointer of pointer
*/
void freeGame(Game **game);

#endif /* GAME */
