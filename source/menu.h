#ifndef MENU
#define MENU

#include "bomberman.h"
#include "utils.h"
#include "files.h"
#include <MLV/MLV_all.h>

typedef enum {
  oNewGame, oLoadGame, oEditor
} Option;

typedef enum {
  oNumberPlayers, oLevel, oStart, oBack
} Option2;

typedef struct{
  int level;
  int numberLevels;
  unsigned int cursor;
  /* Has to be unsigned because used in comparaison with an enum (Option) */
  unsigned int numberOptions;
  unsigned int numberOptions2;
  int numberPlayers;
  int canLoadGame;
  /*
    Phase 0 is the choise between "new game", "load game" or "editor"
    while phase 1 is how many players and what level you want before starting a new game
  */
  int phase;
} Menu;

Menu *initMenu(void);

void menuLoop(Menu *, Bomberman *);

/* Has to be a pointer of pointer */
void freeMenu(Menu **);

#endif /* MENU */
