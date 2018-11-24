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

Leaderboard loadLeaderboard(void);

void saveLeaderboard(Leaderboard);

#endif /* FILES */
