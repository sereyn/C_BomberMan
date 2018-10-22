#ifndef MENU
#define MENU

#include "bomberman.h"
#include "utils.h"

typedef enum {
  oGame, oEditor
} Option;

char *optionToString(Option option);

typedef struct{
  Option cursor;
  /* Has to be unsigned because used in comparaison with an enum (Option) */
  unsigned int optionsNumber;
} Menu;

Menu *initMenu();

void menuLoop(Menu *menu, Bomberman *bbm);

void drawMenu(Menu *menu, Bomberman *bbm);

void freeMenu(Menu *menu);

#endif /* MENU */
