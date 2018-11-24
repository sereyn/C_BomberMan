#include "game.h"

Game *initGame(Bomberman *bbm){
  Game *game = malloc(sizeof(Game));
  int i, j;
  /* We create variables for shorter and clearer code */
  int marginTop = bbm->grid->marginTop;
  Coord *dims = bbm->grid->dimensions;
  int size = bbm->grid->size;
  game->bestPlayer = 0;
  game->highScore = 0;
  game->gameIsOver = 0;
  /* We initializes the players */
  for(i = 0; i < 4; ++i)
    newObject(bbm->players, newCoord(0, 0));
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
  loadLevel(bbm, bbm->level);
  return game;
}

void gameIsOver(Game *game, Bomberman *bbm){
  MLV_Color textColor;
  int colorChangedYet = 0;
  int width = bbm->grid->size*bbm->grid->dimensions->x;
  int height = bbm->grid->size*(bbm->grid->dimensions->y+bbm->grid->marginTop);
  char *endText = malloc(100*sizeof(char));
  char *scoreText;
  int i = 0;
  MLV_draw_filled_rectangle(0, 0, width, height, MLV_COLOR_BLACK);
  sprintf(endText, "Player %d won with a score of %d!", game->bestPlayer+1, game->highScore);
  MLV_draw_text_with_font(
    width/2-bbm->grid->size*2,
    height/4,
    "GAME IS OVER",
    bbm->font,
    MLV_COLOR_WHITE
  );
  MLV_draw_text_with_font(
    width/2-bbm->grid->size*3,
    height/4+bbm->grid->size,
    endText,
    bbm->font,
    MLV_COLOR_WHITE
  );
  MLV_draw_text_with_font(
    width/2-bbm->grid->size*3,
    height/4+bbm->grid->size*2,
    "Press escape to continue",
    bbm->font,
    MLV_COLOR_WHITE
  );
  for(; i < 10; ++i){
    if(game->leaderboard.player[i] == 0)
      break;
    scoreText = malloc(100*sizeof(char));
    sprintf(scoreText, "%d) Player %d : score = %d",
      i+1,
      game->leaderboard.player[i],
      game->leaderboard.score[i]
    );
    textColor = MLV_COLOR_WHITE;
    if(!colorChangedYet
    && game->highScore == game->leaderboard.score[i]
    && game->bestPlayer+1 == game->leaderboard.player[i]){
      textColor = MLV_COLOR_RED;
      colorChangedYet = 1;
    }
    MLV_draw_text_with_font(
      width/2-bbm->grid->size*3,
      (height+bbm->grid->size*i)/2,
      scoreText,
      bbm->font,
      textColor
    );
    free(scoreText);
  }
  free(endText);
}

void gameLoop(Game *game, Bomberman *bbm){
  /* We draw the statistics at the top of the screen */
  int width = bbm->grid->size*bbm->grid->dimensions->x;
  int height = bbm->grid->size*bbm->grid->marginTop;
  int i = 0, j, alivePlayers;
  int currentX;
  char *playerText, *scoreText;
  PlayerVars *playerVars;
  Sprite *sprPlayer;
  if(game->gameIsOver)
    gameIsOver(game, bbm);
  else{
    MLV_draw_filled_rectangle(0, 0, width, height, MLV_COLOR_WHITE);
    /* We loop through all the possible players */
    for(; i < 4; ++i){
      currentX = i*width/4;
      /* We separate the stats per player */
      MLV_draw_line(currentX, 0, currentX, height, MLV_COLOR_BLACK);
      /* We only draw the stats of a player if it exists */
      if(i < bbm->players->length){
        playerText = malloc(25*sizeof(char));
        sprintf(playerText, "Player %d :", i+1);
        MLV_draw_text_with_font(currentX+10, 10, playerText, bbm->font, MLV_COLOR_BLACK);
        free(playerText);
        playerVars = bbm->players->list[i]->variables;
        sprPlayer = bbm->sprPlayerDown[i];
        if(playerVars->dead)
          sprPlayer = bbm->sprPlayerDead;
        drawSprite(sprPlayer, currentX+10, bbm->grid->size+10, 0);
        scoreText = malloc(25*sizeof(char));
        sprintf(scoreText, "Score : %d", playerVars->score);
        MLV_draw_text_with_font(currentX+10, bbm->grid->size*2+10, scoreText, bbm->font, MLV_COLOR_BLACK);
        free(scoreText);
      }
    }
    /* Now we check if one must end the game */
    alivePlayers = 0;
    /* First we count how many players are alive */
    for(i = 0; i < bbm->players->length; ++i){
      playerVars = bbm->players->list[i]->variables;
      if(i == 0){
        game->highScore = playerVars->score;
        game->bestPlayer = 0;
      }else{
        if(playerVars->score > game->highScore){
          game->highScore = playerVars->score;
          game->bestPlayer = i;
        }
      }
      if(!playerVars->dead)
        alivePlayers++;
    }
    /* Now if one or less players are alive, we end the game */
    if(alivePlayers <= 1){
      game->gameIsOver = 1;
      debug(0, "Game is over, saving score...\n");
      game->leaderboard = loadLeaderboard();
      for(i = 0; i < 10; ++i){
        /*
          If the current high score is better than the one we're checking in the list
          OR if we don't yet saved any score here
        */
        if(game->highScore >= game->leaderboard.score[i] || game->leaderboard.player[i] == 0){
          /* We move all the rest of the scores one range lower */
          for(j = 9; j > i; --j){
            game->leaderboard.player[j] = game->leaderboard.player[j-1];
            game->leaderboard.score[j] = game->leaderboard.score[j-1];
          }
          /* We add our score */
          game->leaderboard.player[i] = game->bestPlayer+1;
          game->leaderboard.score[i] = game->highScore;
          break;
        }
      }
      /* Finally we save the new leaderboard */
      saveLeaderboard(game->leaderboard);
    }
  }
}

void freeGame(Game **game){
  /* We make it being a pointer of pointer so that we can set it to point on NULL */
  if(*game){
    free(*game);
    *game = NULL;
  }
}
