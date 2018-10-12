#ifndef GAME
#define GAME

#include "utils.h"
#include "files.h"
#include "objects.h"

typedef struct {
  /**/
} Game;

/* Inits the game */
Game *initGame(Bomberman *bbm);

/* Has to be executed in a game loop: main function of the game */
void gameLoop(Game *game, Bomberman *bbm);

/* Frees the game */
void freeGame(Game *game);

#endif /* GAME */
