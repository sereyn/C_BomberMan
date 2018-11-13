#ifndef BONUS
#define BONUS

#include "../objects.h"
#include "../sprites.h"
#include "player.h"
#include "../utils.h"

typedef enum {
  bFlame, bBomb, bSpeed
} BonusType;

typedef struct {
  BonusType bonusType;
} BonusVars;

void initBonus(int index, void *bbmVoid);

void updateBonus(int index, void *bbmVoid);

#endif /* BONUS */
