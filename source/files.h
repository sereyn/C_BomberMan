#ifndef FILES
#define FILES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "bomberman.h"
#include "objects.h"

typedef struct {
  int score[10];
  int player[10];
} Leaderboard;

/* Counts how many levels exist */
int countLevels(void);

/* Saves a level */
void saveLevel(Bomberman *);

/* Loads a level */
void loadLevel(Bomberman *, int fileNumber);

/* Reads the leaderboard */
Leaderboard loadLeaderboard(void);

/* Saves the leaderboard */
void saveLeaderboard(Leaderboard);

/* Checkes wether or not a game is saved */
int gameExists(void);

/* Saves the game */
void saveGame(Bomberman *);

/* Loads the game */
void loadGame(Bomberman *);

#endif /* FILES */
