#include "game.h"

Game *initGame(Bomberman *bbm){
  Game *game = malloc(sizeof(Game));
  loadLevel(bbm, 0);
  return game;
}

void gameLoop(Game *game, Bomberman *bbm){
  /* */
}

void freeGame(Game *game){
  /* Frees the game */
  free(game);
}
