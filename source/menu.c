#include "menu.h"

char *optionToString(Option option){
  switch(option){
    case oNewGame:
      return "New Game";
    case oLoadGame:
      return "Load Game";
    case oEditor:
      return "Editor";
  }
  return "";
}

Menu *initMenu(void){
  /* We initialize the menu */
  Menu *menu = malloc(sizeof(Menu));
  menu->level = 0;
  menu->numberLevels = countLevels();
  menu->numberPlayers = 2;
  menu->cursor = oNewGame;
  menu->numberOptions = 3;
  menu->numberOptions2 = 4;
  menu->canLoadGame = gameExists();
  menu->phase = 0;
  return menu;
}

void drawMenu(Menu *menu, Bomberman *bbm){
  MLV_Color textColor = MLV_COLOR_WHITE;
  unsigned int i;
  int size = bbm->grid->size;
  int marginLeft = 2, marginTop = 3;
  char *optionText;
  /* We show the title */
  MLV_draw_text_with_font(
    marginLeft*size, marginTop*size,
    "BOMBERMAN", bbm->font, MLV_COLOR_WHITE);
  /* Now it all depends of on which phase of the menu we are on */
  if(menu->phase == 0){
    /* Phase 0: We show all the options */
    for(i = 0; i < menu->numberOptions; ++i){
      optionText = malloc(25*sizeof(char));
      sprintf(optionText, "%s%s", optionToString(i), i == menu->cursor ? " <" : "");
      if(i == oLoadGame && !menu->canLoadGame)
        textColor = MLV_COLOR_DARK_GRAY;
      else
        textColor = MLV_COLOR_WHITE;
      MLV_draw_text_with_font(
        marginLeft*size, (marginTop+4+i)*size,
        optionText, bbm->font, textColor);
      free(optionText);
    }
  }else if(menu->phase == 1){
    /* Phase 1 */
    for(i = 0; i < menu->numberOptions2; ++i){
      optionText = malloc(25*sizeof(char));
      /*
        We set the current level formatted in 'LevelText'
        (we add one because it feels more natural for users to start counting at 1
      */
      switch(i){
        case oNumberPlayers:
          sprintf(optionText, "%s%d", "Number of players: ", menu->numberPlayers);
          break;
        case oLevel:
          sprintf(optionText, "%s%d", "Level: ", menu->level+1);
          break;
        case oStart:
          sprintf(optionText, "%s", "Start");
          break;
        case oBack:
          sprintf(optionText, "%s", "Back");
          break;
      }
      sprintf(optionText, "%s%s", optionText, i == menu->cursor ? " <" : "");
      MLV_draw_text_with_font(
        marginLeft*size, (marginTop+4+i)*size,
        optionText, bbm->font, textColor);
      free(optionText);
    }
  }
}

void menuLoop(Menu *menu, Bomberman *bbm){
  if(menu->phase == 0){
    /* We move the cursor if the user presses up or down */
    if(isJustDown(bbm->inputs->down))
      menu->cursor += menu->cursor < menu->numberOptions-1;
    if(isJustDown(bbm->inputs->up))
      menu->cursor -= menu->cursor > 0;
    /* If the cursor is on Load Game and we can't, we skip the selection */
    if(menu->cursor == oLoadGame && !menu->canLoadGame){
      menu->cursor += isJustDown(bbm->inputs->down)-isJustDown(bbm->inputs->up);
    }
    if(isJustDown(bbm->inputs->enter)){
      debug(4, "Menu choice: '%s'\n", optionToString(menu->cursor));
      switch(menu->cursor){
        case oNewGame:
          menu->phase = 1;
          menu->cursor = oStart;
          break;
        case oLoadGame:
          bbm->loading = 1;
          loadGame(bbm);
          break;
        case oEditor:
          setState(bbm, sEditor);
          break;
      }
    }
  }else if(menu->phase == 1){
    /* We move the cursor if the user presses up or down */
    if(isJustDown(bbm->inputs->down))
      menu->cursor += menu->cursor < menu->numberOptions2-1;
    if(isJustDown(bbm->inputs->up))
      menu->cursor -= menu->cursor > 0;
    switch(menu->cursor){
      case oNumberPlayers:
        if(isJustDown(bbm->inputs->right))
          menu->numberPlayers += menu->numberPlayers < 4;
        if(isJustDown(bbm->inputs->left))
          menu->numberPlayers -= menu->numberPlayers > 2;
        break;
      case oLevel:
        if(isJustDown(bbm->inputs->right))
          menu->level += menu->level < menu->numberLevels-1;
        if(isJustDown(bbm->inputs->left))
          menu->level -= menu->level > 0;
        break;
      case oStart:
        if(isJustDown(bbm->inputs->enter)){
          debug(4, "Start the game!\n");
          bbm->level = menu->level;
          bbm->numberPlayers = menu->numberPlayers;
          bbm->loading = 0;
          setState(bbm, sGame);
        }
        break;
      case oBack:
        if(isJustDown(bbm->inputs->enter)){
          debug(4, "Back to phase 0\n");
          menu->phase = 0;
          menu->cursor = oNewGame;
        }
        break;
    }
  }
  /* We draw the menu */
  drawMenu(menu, bbm);
}

void freeMenu(Menu **menu){
  /* We make it being a pointer of pointer so that we can set it to point on NULL */
  if(*menu){
    free(*menu);
    *menu = NULL;
  }
}
