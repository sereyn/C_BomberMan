#ifndef GAME
#define GAME

#include "utils.h"
#include "files.h"
#include "objects.h"
#include "objects/player.h"
#include "sprites.h"
#include <MLV/MLV_all.h>

typedef struct{
  int highScore;
  int bestPlayer;
  int gameIsOver;
  Leaderboard leaderboard;
} Game;

/* Inits the game */
Game *initGame(Bomberman *);

/* Draws the statistics */
void gameLoop(Game *, Bomberman *);

/* Has to be a pointer of pointer */
void freeGame(Game **);

#endif /* GAME */
