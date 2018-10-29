#ifndef FILES
#define FILES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "bomberman.h"
#include "objects.h"

/* Counts how many levels exist */
int countLevels();

/* Saves a level */
void saveLevel(Bomberman *bbm);

/* Loads a level */
void loadLevel(Bomberman *bbm, int fileNumber);

#endif /* FILES */