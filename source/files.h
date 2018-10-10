#ifndef FILES
#define FILES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "bomberman.h"
#include "objects.h"

/* Saves a level */
void saveLevel(Bomberman *bbm);

/* Loads a level */
void loadLevel();

#endif /* FILES */