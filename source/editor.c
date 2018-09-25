#include "editor.h"

void initEditor(Bomberman *bbm){
  int marginTop = 3;
  int i, j;
  int gridSize = bbm->gridSize;
  for(i = 0; i < MLV_get_window_width()/gridSize; ++i){
    for(j = marginTop; j < MLV_get_window_height()/gridSize; ++j){
      if(i == 0 || j == 3
      || i == MLV_get_window_width()/gridSize-1
      || j == MLV_get_window_height()/gridSize-1)
        newObject(&(bbm->blocks), i, j);
      else
        newObject(&(bbm->floors), i, j);
    }
  }
}

void editorLoop(Bomberman *bbm){
  int mouseX, mouseY, i;
  int marginTop = 3;
  MLV_get_mouse_position(&mouseX, &mouseY);
  if(mouseX > bbm->gridSize && mouseX < MLV_get_window_width()-bbm->gridSize
  && mouseY > (1+marginTop)*bbm->gridSize && mouseY < MLV_get_window_height()-bbm->gridSize){
    if(!MLV_get_mouse_button_state(MLV_BUTTON_LEFT)){
      newObject(&(bbm->blocks), (mouseX)/bbm->gridSize, (mouseY)/bbm->gridSize);
    }
    if(!MLV_get_mouse_button_state(MLV_BUTTON_RIGHT)){
      for(i = 0; i < bbm->blocks.length; ++i){
        if(mouseX/bbm->gridSize == bbm->blocks.list[i].x
        && mouseY/bbm->gridSize == bbm->blocks.list[i].y){
          deleteObject(&(bbm->blocks), i);
        }
      }
    }
  }
}
