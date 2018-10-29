#include "menu.h"

char *optionToString(Option option){
  switch(option){
    case oGame:
      return "Play";
    case oEditor:
      return "Editor";
  }
  return "";
}

Menu *initMenu(){
  /* We initialize the menu */
  Menu *menu = malloc(sizeof(Menu));
  menu->level = 0;
  menu->levelsNumber = countLevels();
  menu->cursor = oGame;
  menu->optionsNumber = 2;
  return menu;
}

void menuLoop(Menu *menu, Bomberman *bbm){
  /* We move the cursor if the user presses up or down */
  if(isJustDown(bbm->inputs->down))
    menu->cursor += menu->cursor < menu->optionsNumber-1;
  if(isJustDown(bbm->inputs->up))
    menu->cursor -= menu->cursor > 0;
  /* If the user is currently selecting the 'Game option' */
  if(menu->cursor == oGame){
    /* We change the level if he presses right or left */
    if(isJustDown(bbm->inputs->right))
      menu->level += menu->level < menu->levelsNumber-1;
    if(isJustDown(bbm->inputs->left))
      menu->level -= menu->level > 0;
  }
  /* We draw the menu */
  drawMenu(menu, bbm);
  /* If the user presses enter, we select their choice */
  if(isJustDown(bbm->inputs->enter)){
    debug(4, "Menu choice: '%s'\n", optionToString(menu->cursor));
    /* We set bbm->level to be menu->level so that it starts the accurate level */
    bbm->level = menu->level;
    /* bbm->state fits menu->cursor+1 so we enjoy its benefits */
    setState(bbm, menu->cursor+1);
  }
}

void drawMenu(Menu *menu, Bomberman *bbm){
  unsigned int i = 0;
  int size = bbm->grid->size;
  int marginLeft = 2, marginTop = 3;
  char *levelText = malloc(20*sizeof(char));
  char *optionText;
  /*
    Set the current level formatted in 'LevelText'
    (we add one because it feels more natural for users to start counting at 1
  */
  sprintf(levelText, ": level[%d]", menu->level+1);
  /* Show the title */
  MLV_draw_text_with_font(
    marginLeft*size, marginTop*size,
    "BOMBERMAN", bbm->font, MLV_COLOR_WHITE);
  /* Show all the options */
  for(; i < menu->optionsNumber; ++i){
    optionText = malloc(25*sizeof(char));
    /* Copy the current option into optionText */
    strcpy(optionText, optionToString(i));
    /* If the option is set to "Game", we append the level number to the string */
    if(i == oGame)
      strcat(optionText, levelText);
    /* If the cursor is currently selecting this option, we concat to this string an arrow */
    if(i == menu->cursor)
      strcat(optionText, " <");
    MLV_draw_text_with_font(
      marginLeft*size, (marginTop+4+i)*size,
      optionText, bbm->font, MLV_COLOR_GRAY);
    free(optionText);
  }
  free(levelText);
  /* Temporarily draw animations for test purposes */
  drawAnimation(bbm->aniBomb, size*15, size*5);
  drawAnimation(bbm->aniFlameCenter, size*14, size*4);
  drawAnimation(bbm->aniFlameXSide, size*13, size*4);
  drawAnimation(bbm->aniFlameXSide, size*15, size*4);
  drawAnimation(bbm->aniFlameYSide, size*14, size*3);
  drawAnimation(bbm->aniFlameYSide, size*14, size*5);
  drawAnimation(bbm->aniFlameRightTip, size*16, size*4);
  drawAnimation(bbm->aniFlameLeftTip, size*12, size*4);
  drawAnimation(bbm->aniFlameDownTip, size*14, size*6);
  drawAnimation(bbm->aniFlameUpTip, size*14, size*2);
}

void freeMenu(Menu **menu){
  /* We make it being a pointer of pointer so that we can set it to point on NULL */
  if(*menu){
    free(*menu);
    *menu = NULL;
  }
}
