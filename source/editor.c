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
		newBlock(&(bbm->blocks), i, j);
	  else
		newFloor(&(bbm->floors), i, j);
	}
  }
}

void editorLoop(Bomberman *bbm){
  int mouseX, mouseY;
  int i;
  int blockClickedFound = 0;
  if(!MLV_get_mouse_button_state(MLV_BUTTON_LEFT)){
	MLV_get_mouse_position(&mouseX, &mouseY);
	newBlock(&(bbm->blocks), (mouseX)/bbm->gridSize, (mouseY)/bbm->gridSize);
  }
  if(!MLV_get_mouse_button_state(MLV_BUTTON_RIGHT)){
	MLV_get_mouse_position(&mouseX, &mouseY);
	/* TODO: Create remove block function */
	for(i=0; i<bbm->blocks.length; i++){
	  if(blockClickedFound){
		bbm->blocks.list[i-1] = bbm->blocks.list[i];
	  }
	  if((int)(mouseX)/bbm->gridSize == bbm->blocks.list[i].x && (int)(mouseY)/bbm->gridSize == bbm->blocks.list[i].y){
		blockClickedFound = 1;
	  }
	}
	if(blockClickedFound){
	  bbm->blocks.list = realloc(bbm->blocks.list, --bbm->blocks.length);
	}
  }
}
