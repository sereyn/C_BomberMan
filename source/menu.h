#ifndef MENU
#define MENU

#include "bomberman.h"
#include "utils.h"
#include "files.h"

typedef enum {
  oGame, oEditor
} Option;

typedef struct{
  int level;
  int levelsNumber;
  Option cursor;
  /* Has to be unsigned because used in comparaison with an enum (Option) */
  unsigned int optionsNumber;
} Menu;

Menu *initMenu(void);

void menuLoop(Menu *, Bomberman *);

/* Has to be a pointer of pointer */
void freeMenu(Menu **);

#endif /* MENU */
