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
  /* We draw the menu */
  drawMenu(menu, bbm);
  /* If the user presses enter, we select their choice */
  if(isJustDown(bbm->inputs->enter)){
    debug(4, "Menu choice: '%s'\n", optionToString(menu->cursor));
    /* bbm->state fits menu->cursor+1 so we enjoy its benefits */
    bbm->state = menu->cursor+1;
  }
}

void drawMenu(Menu *menu, Bomberman *bbm){
  unsigned int i = 0;
  int size = bbm->grid->size;
  int marginLeft = 2, marginTop = 3;
  char *optionText;
  /* Show the title */
  MLV_draw_text_with_font(
    marginLeft*size, marginTop*size,
    "BOMBERMAN", bbm->font, MLV_COLOR_WHITE);
  /* Show all the options */
  for(; i < menu->optionsNumber; ++i){
    optionText = malloc(15*sizeof(char));
    /* Copy the current option into optionText */
    strcpy(optionText, optionToString(i));
    /* If the cursor is currently selecting this option, we concat to this string an arrow */
    if(i == menu->cursor)
      strcat(optionText, " <");
    MLV_draw_text_with_font(
      marginLeft*size, (marginTop+4+i)*size,
      optionText, bbm->font, MLV_COLOR_GRAY);
    free(optionText);
  }
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

void freeMenu(Menu *menu){
  if(menu){
    free(menu);
    menu = NULL;
  }
}
