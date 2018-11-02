#ifndef OBJPROPS
#define OBJPROPS

#include "objects.h"
#include "sprites.h"
#include "inputs.h"
#include <math.h>

/* Here we define all the object properties */

/* Initialisations */
void initBomb(int index, void *bbmVoid);

void initFlame(int index, void *bbmVoid);

void initPlayer(int index, void *bbmVoid);

/* Updates */
void updateBomb(int index, void *bbmVoid);

void updateFlame(int index, void *bbmVoid);

void updatePlayer(int index, void *bbmVoid);

#endif /* OBJPROPS */
