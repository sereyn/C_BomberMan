#ifndef FLAME
#define FLAME

#include "../objects.h"
#include "../sprites.h"

typedef struct {
  int player;
} FlameVars;

void initFlame(int index, void *bbmVoid);

void updateFlame(int index, void *bbmVoid);

#endif /* FLAME */
