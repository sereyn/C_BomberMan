#include "game.h"

Game *initGame(Bomberman *bbm){
  int i, j;
  /* We create variables for shorter and clearer code */
  int marginTop = bbm->grid->marginTop;
  Coord *dims = bbm->grid->dimensions;
  int size = bbm->grid->size;
  Game *game = malloc(sizeof(Game));
  /* We initializes the players */
  for(i = 0; i < 4; ++i)
    game->players[i] = newPlayer(bbm, i);
  /* We create the objects that will always be in the same place */
  debug(1, "Filling the game grid\n");
  for(i = 0; i < dims->x; ++i){
    for(j = 0; j < dims->y; ++j){
      /* If we are at the edge of the board, we create a block */
      if(i == 0 || j == 0
      || i == dims->x-1 || j == dims->y-1)
        newObject(bbm->blocks, newCoord(i*size, (j+marginTop)*size));
      /* Otherwise we create a floor */
      else
        newObject(bbm->floors, newCoord(i*size, (j+marginTop)*size));
    }
  }
  /* Now we add the objects that depend of each level */
  loadLevel(bbm, 1);
  return game;
}

void gameLoop(Game *game, Bomberman *bbm){
  int i;
  /* We update the 4 players */
  for(i = 0; i < 4; ++i)
    updatePlayer(game->players[i], bbm);
}

void freeGame(Game *game){
  int i = 0;
  if(game){
    /* Frees the game */
    for(; i < 4; ++i)
      freePlayer(game->players[i]);
    free(game);
    game = NULL;
  }
}
