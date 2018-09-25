#include "editor.h"

void initEditor(Bomberman *bbm){
  /* marginTop is the top space for hub interface */
  int marginTop = 3;
  int i, j;
  /* We let size be the gridSize of bomberman for shorter and clearer code */
  int size = bbm->gridSize;
  /* We loop through the whole board */
  for(i = 0; i < MLV_get_window_width(); i += size){
    for(j = size*marginTop; j < MLV_get_window_height(); j += size){
      /* If we are at the edge of the board, we create a block */
      if(i == 0 || j == marginTop*size
      || i == MLV_get_window_width()-size
      || j == MLV_get_window_height()-size)
        newObject(&(bbm->blocks), i, j);
      /* Otherwise we create a floor */
      else
        newObject(&(bbm->floors), i, j);
    }
  }
}

void editorLoop(Bomberman *bbm){
  int mouseX, mouseY, i;
  int marginTop = 3;
  /* We store the mouse position into mouseX and mouseY variables */
  MLV_get_mouse_position(&mouseX, &mouseY);
  /*
    We check if the mouse cursor is inside the board
    (edge blocks excluded, as we don't want the user to edit those ones)
  */
  if(mouseX > bbm->gridSize && mouseX < MLV_get_window_width()-bbm->gridSize
  && mouseY > (1+marginTop)*bbm->gridSize && mouseY < MLV_get_window_height()-bbm->gridSize){
    if(!MLV_get_mouse_button_state(MLV_BUTTON_LEFT)){
      /*
        If the left click is pressed,
        we create a block at the mouse coordinates divided then multiplied by gridSize
        since they are all integers, it maps the coordinates to the grid
      */
      newObject(
        &(bbm->blocks),
        mouseX/bbm->gridSize*bbm->gridSize,
        mouseY/bbm->gridSize*bbm->gridSize
      );
    }
    if(!MLV_get_mouse_button_state(MLV_BUTTON_RIGHT)){
      /*
        If the right click is pressed,
        we loop through every block and check if the mouse is over it
        If that's the case, then we remove that block
      */
      for(i = 0; i < bbm->blocks.length; ++i){
        if(mouseX/bbm->gridSize == bbm->blocks.list[i].x/bbm->gridSize
        && mouseY/bbm->gridSize == bbm->blocks.list[i].y/bbm->gridSize){
          deleteObject(&(bbm->blocks), i);
        }
      }
    }
  }
}
