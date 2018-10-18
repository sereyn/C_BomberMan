#include "menu.h"

Menu *initMenu(int state){
  Menu *menu = malloc(sizeof(Menu));
  menu->state = state;
  menu->stateFocused = 1;
  menu->keyReleased = 1;
  menu->statesLength = 2;
  return menu;
}

void menuLoop(Menu *menu, Game *game, Editor *editor, Bomberman *bbm){
  Player *mainPlayer = game->players[0];
  int ySpeed = isDown(mainPlayer->down)-isDown(mainPlayer->up);

  /* ------ Cases: not in menu ------ */
	if(menu->state == 1){
    if(!game->created)
      createGame(game, bbm);
		return gameLoop(game, bbm);
  }
	if(menu->state == 2){
    if(!editor->created)
      createEditor(editor, bbm);
		return editorLoop(editor, bbm);
  }

  /* ------ Case: in menu ------ */

  /* Move the focus */
  if(menu->keyReleased){
    menu->keyReleased = 0;
    if(ySpeed < 0 && menu->stateFocused > 1){
      menu->stateFocused -= 1;
    }else if(ySpeed > 0 && menu->stateFocused < 2){
      menu->stateFocused += 1;
    }else{
      menu->keyReleased = 1;
    }
  }else if(ySpeed == 0){
    menu->keyReleased = 1;
    debug(4, "Menu choice: %d\n", menu->stateFocused);
  }
  /* Draw menu */
  drawMenu(menu, bbm);
}

void drawMenu(Menu *menu, Bomberman *bbm){
  char editorText[15] = "  Editor  ";
  char playText[15] = "  Play  ";
  Coord *dims = bbm->grid->dimensions;
  int size = bbm->grid->size;
  /* Apply text */
  if(menu->stateFocused == 1){
    strcpy(playText, "< Play >");
  }else{
    strcpy(editorText, "< Editor >");
  }
  /* Hide game behind menu */
  MLV_clear_window(MLV_COLOR_BLACK);
  /* Draw title */
  MLV_draw_text_with_font(
    dims->x/2*size,
    size*.02,
    "BomberMan", bbm->font, MLV_COLOR_WHITE);
  /* Draw  choices */
  MLV_draw_text_with_font(
    dims->x/2*size,
    size*4,
    playText, bbm->font, MLV_COLOR_GRAY);
  MLV_draw_text_with_font(
    dims->x/2*size,
    size*5,
    editorText, bbm->font, MLV_COLOR_GRAY);
  /* On left ctrl, change state */
  if(isJustDown(bbm->inputs->lctrl)){
    menu->state = menu->stateFocused;
  }
}