#ifndef MENU
#define MENU

#include "game.h"
#include "editor.h"
#include "bomberman.h"

typedef struct{
  int state; /* 0:menu 1:game 2:editor */
  int stateFocused;
  int keyReleased;
  int statesLength;
} Menu;

Menu *initMenu(int state);

void menuLoop(Menu *menu, Game *game, Editor *editor, Bomberman *bbm);

#endif /* MENU */