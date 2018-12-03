#include "files.h"
#include "objects/bomb.h"
#include "objects/flame.h"
#include "objects/bonus.h"
#include "objects/player.h"

int countLevels(void){
  int fileNumber = 0;
  char *prefix = "resources/levels/lvl";
  /*
    We alloc the needed memory to path for it to prefix+fileNumber
    The +5 lets the fileNumber be a 4 digit number (base 10)
    Why 4 and not 5? That's because the last memory slot if dedicated for the \0 at the end
  */
  char *path = malloc((strlen(prefix)+strlen(prefix)+5)*sizeof(char));
  /*
    While the file path exists, we iterate fileNumber
    We check if a file exists using access, from unistd.h
  */
  do
    sprintf(path, "%s%d", prefix, fileNumber++);
  while(access(path, F_OK) != -1);
  return fileNumber-1;
}

void saveLevel(Bomberman *bbm){
  int fileNumber = 0, i, j, x, y;
  char *prefix = "resources/levels/lvl";
  FILE *lvl;
  /*
    We alloc the needed memory to path for it to prefix+fileNumber
    The +5 lets the fileNumber be a 4 digit number (base 10)
    Why 4 and not 5? That's because the last memory slot if dedicated for the \0 at the end
  */
  char *path = malloc((strlen(prefix)+strlen(prefix)+5)*sizeof(char));
  /* o stands for blocks, c for boxes and s for spikes */
  char *objChars = "bcs";
  Objects *objList[3];
  objList[0] = bbm->blocks;
  objList[1] = bbm->boxes;
  objList[2] = bbm->spikes;
  /*
    While the file path exists, we iterate fileNumber
    We check if a file exists using access, from unistd.h
  */
  do
    sprintf(path, "%s%d", prefix, fileNumber++);
  while(access(path, F_OK) != -1);
  lvl = fopen(path, "w");
  /* We can free path */
  free(path);
  if(!lvl)
    exit(EXIT_FAILURE);
  /* We save all blocks, boxes and spikes */
  for(j = 0; j < 3; ++j){
    fprintf(lvl, "%c\n", objChars[j]);
    for(i = 0; i < objList[j]->length; ++i){
      x = objList[j]->list[i]->position->x/bbm->grid->size;
      y = objList[j]->list[i]->position->y/bbm->grid->size;
      if(x > 0 && x < bbm->grid->dimensions->x-1
      && y > bbm->grid->marginTop && y < bbm->grid->marginTop+bbm->grid->dimensions->y-1)
        fprintf(lvl, "%d;%d\n", x, y);
    }
  }
  fclose(lvl);
  debug(0, "Level saved!\n");
}

void loadLevel(Bomberman *bbm, int fileNumber){
  int i, x, y;
  int xBonus, yBonus;
  int bonusMargin = (bbm->grid->size-bbm->bonus->defSprite->dimensions->x)/2;
  char objChar;
  char *prefix = "resources/levels/lvl";
  /* Same as in saveLevel */
  char *path = malloc((strlen(prefix)+5)*sizeof(char));
  FILE *lvl;
  Objects *objList[3];
  objList[0] = bbm->blocks;
  objList[1] = bbm->boxes;
  objList[2] = bbm->spikes;
  sprintf(path, "%s%d", prefix, fileNumber);
  lvl = fopen(path, "r");
  if(!lvl)
    exit(EXIT_FAILURE);
  for(i = 0; i < 3; ++i){
    if(fscanf(lvl, "%c", &objChar) == 1){
      if(objChar == "bcs"[i]){
        while(fscanf(lvl, "%d;%d", &x, &y) == 2){
          newObject(objList[i], newCoord(x*bbm->grid->size, y*bbm->grid->size));
          if(objChar == 'c' && rand()%100 < 20){
            xBonus = x*bbm->grid->size+bonusMargin;
            yBonus = y*bbm->grid->size+bonusMargin;
            newObject(bbm->bonus, newCoord(xBonus, yBonus));
          }
        }
      }
    }
  }
  fclose(lvl);
  free(path);
}

Leaderboard loadLeaderboard(void){
  Leaderboard leaderboard;
  int i = 0, player, score;
  FILE *file;
  for(; i < 10; ++i){
    leaderboard.score[i] = 0;
    leaderboard.player[i] = 0;
  }
  file = fopen("resources/leaderboard", "r");
  if(!file)
    debug(0, "No leaderboard yet\n");
  else{
    for(i = 0; fscanf(file, "%d;%d", &player, &score) == 2 && i < 10; ++i){
      leaderboard.score[i] = score;
      leaderboard.player[i] = player;
    }
    fclose(file);
  }
  return leaderboard;
}

void saveLeaderboard(Leaderboard leaderboard){
  int i = 0;
  FILE *file = fopen("resources/leaderboard", "w");
  if(!file)
    exit(EXIT_FAILURE);
  for(; i < 10; ++i){
    if(leaderboard.player[i] == 0)
      break;
    fprintf(file, "%d;%d\n", leaderboard.player[i], leaderboard.score[i]);
  }
  fclose(file);
}

int gameExists(void){
  return (access("resources/game", F_OK) != -1);
}

void saveGame(Bomberman *bbm){
  int i, j, x, y;
  BombVars *bombVars;
  FlameVars *flameVars;
  BonusVars *bonusVars;
  PlayerVars *playerVars;
  FILE *fGame;
  char objKeywords[7][10];
  Objects *objList[7];
  Object *obj;
  sprintf(objKeywords[0], "blocks");
  sprintf(objKeywords[1], "boxes");
  sprintf(objKeywords[2], "spikes");
  sprintf(objKeywords[3], "bombs");
  sprintf(objKeywords[4], "flames");
  sprintf(objKeywords[5], "bonus");
  sprintf(objKeywords[6], "players");
  objList[0] = bbm->blocks;
  objList[1] = bbm->boxes;
  objList[2] = bbm->spikes;
  objList[3] = bbm->bombs;
  objList[4] = bbm->flames;
  objList[5] = bbm->bonus;
  objList[6] = bbm->players;
  if(!(fGame = fopen("resources/game", "w")))
    exit(EXIT_FAILURE);
  for(j = 0; j < 7; ++j){
    fprintf(fGame, "%s\n", objKeywords[j]);
    for(i = 0; i < objList[j]->length; ++i){
      obj = objList[j]->list[i];
      x = obj->position->x;
      y = obj->position->y;
      if(j != 6){
        /*
          If we're not saving the player coordinates,
          we divide them by the grid size since they're already mapped to the grid
        */
        x /= bbm->grid->size;
        y /= bbm->grid->size;
      }
      fprintf(fGame, "%d;%d", x, y);
      /* We add extra informations to save depending of the object */
      switch(j){
        case 3: /* bomb */
          bombVars = obj->variables;
          fprintf(fGame, ";%d;%f",
            bombVars->player,
            obj->sprIndex
          );
          break;
        case 4: /* flame */
          flameVars = obj->variables;
          fprintf(fGame, ";%d;%f",
            flameVars->player,
            obj->sprIndex
          );
          break;
        case 5: /* bonus */
          bonusVars = obj->variables;
          fprintf(fGame, ";%d", bonusVars->bonusType);
          break;
        case 6: /* player */
          playerVars = obj->variables;
          fprintf(fGame, ";%d;%d;%d;%d;%d;%f",
            playerVars->score,
            playerVars->flameLength,
            playerVars->bombThrown,
            playerVars->bombMax,
            playerVars->dead,
            playerVars->speed
          );
          break;
      }
      fprintf(fGame, "\n");
    }
  }
  fclose(fGame);
  debug(0, "Game saved!\n");
}

void loadGame(Bomberman *bbm){
  int i, j, size = bbm->grid->size;
  int marginTop = bbm->grid->marginTop;
  Coord *dims = bbm->grid->dimensions;
  int x, y, player, bonusType, score, flameLength, bombThrown, bombMax, dead;
  int bonusMargin = (size-bbm->bonus->defSprite->dimensions->x)/2;
  double sprIndex, speed;
  BombVars *bombVars;
  FlameVars *flameVars;
  BonusVars *bonusVars;
  PlayerVars *playerVars;
  FILE *fGame;
  char objKeywords[7][10];
  char objKeyword[10];
  Objects *objList[7];
  Object *obj;
  sprintf(objKeywords[0], "blocks");
  sprintf(objKeywords[1], "boxes");
  sprintf(objKeywords[2], "spikes");
  sprintf(objKeywords[3], "bombs");
  sprintf(objKeywords[4], "flames");
  sprintf(objKeywords[5], "bonus");
  sprintf(objKeywords[6], "players");
  /* We set the number of players to 0 and will increment it as reading the file */
  bbm->numberPlayers = 0;
  setState(bbm, sGame);
  /*
    We make sure to make the objList after we change the state
    because bbm can change its pointers
  */
  objList[0] = bbm->blocks;
  objList[1] = bbm->boxes;
  objList[2] = bbm->spikes;
  objList[3] = bbm->bombs;
  objList[4] = bbm->flames;
  objList[5] = bbm->bonus;
  objList[6] = bbm->players;
  for(i = 0; i < dims->x; ++i){
    for(j = 0; j < dims->y; ++j)
      newObject(bbm->floors, newCoord(i*size, (j+marginTop)*size));
  }
  debug(0, "Loading game...\n");
  if(!(fGame = fopen("resources/game", "r")))
    exit(EXIT_FAILURE);
  for(j = 0; j < 7; ++j){
    /* We read a keyword */
    if(fscanf(fGame, "%s", objKeyword) == 1){
      /* If nothing went wrong */
      if(strcmp(objKeyword, objKeywords[j]) == 0){
        /* We check what we are reading (j) */
        switch(j){
          case 0: /* block */
          case 1: /* box */
          case 2: /* spike */
            while(fscanf(fGame, "%d;%d", &x, &y) == 2)
              newObject(objList[j], newCoord(x*size, y*size));
            break;
          case 3: /* bomb */
            while(fscanf(fGame, "%d;%d;%d;%lf", &x, &y, &player, &sprIndex) == 4){
              obj = newObject(objList[j], newCoord(x*size, y*size));
              obj->sprIndex = sprIndex;
              bombVars = obj->variables;
              bombVars->player = player;
            }
            break;
          case 4: /* flame */
            while(fscanf(fGame, "%d;%d;%d;%lf", &x, &y, &player, &sprIndex) == 4){
              obj = newObject(objList[j], newCoord(x*size, y*size));
              obj->sprIndex = sprIndex;
              flameVars = obj->variables;
              flameVars->player = player;
            }
            break;
          case 5: /* bonus */
            while(fscanf(fGame, "%d;%d;%d", &x, &y, &bonusType) == 3){
              obj = newObject(objList[j], newCoord(x*size, y*size));
              obj->position->x += bonusMargin;
              obj->position->y += bonusMargin;
              bonusVars = obj->variables;
              bonusVars->bonusType = bonusType;
              switch(bonusType){
                case 0:
                  obj->sprite = bbm->sprBonusFlame;
                  break;
                case 1:
                  obj->sprite = bbm->sprBonusBomb;
                  break;
                case 2:
                  obj->sprite = bbm->sprBonusSpeed;
                  break;
              }
            }
            break;
          case 6: /* player */
            while(fscanf(fGame, "%d;%d;%d;%d;%d;%d;%d;%lf", &x, &y,
              &score, &flameLength, &bombThrown, &bombMax, &dead, &speed) == 8){
              obj = newObject(objList[j], newCoord(0, 0));
              obj->position->x = x;
              obj->position->y = y;
              playerVars = obj->variables;
              playerVars->score = score;
              playerVars->flameLength = flameLength;
              playerVars->bombThrown = bombThrown;
              playerVars->bombMax = bombMax;
              playerVars->dead = dead;
              playerVars->speed = speed;
              bbm->numberPlayers++;
            }
            break;
        }
      }
    }
  }
  fclose(fGame);
  /* Finally we remove the file */
  remove("resources/game");
}
