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
	if(!MLV_get_mouse_button_state(MLV_BUTTON_LEFT)){
		MLV_get_mouse_position(&mouseX, &mouseY);
		newBlock(&(bbm->blocks), (mouseX)/bbm->gridSize, (mouseY)/bbm->gridSize);
	}
}
