#include "editor.h"

Editor initEditor(Bomberman *bbm){
  Editor editor;
  int i, j;
  int winWidth = MLV_get_window_width(), winHeight = MLV_get_window_height();
  /* We let size be the gridSize of bomberman for shorter and clearer code */
  int size = bbm->gridSize;
  /*
    We evaluate the marginTop
    It represents the number of blocks to skip at the top of the grid
  */
  int marginTop = winHeight/bbm->gridSize-bbm->gridDimensions.y;
  /* We loop through the whole board */
  for(i = 0; i < winWidth; i += size){
    for(j = marginTop*size; j < winHeight; j += size){
      /* If we are at the edge of the board, we create a block */
      if(i == 0 || j == marginTop*size
      || i == winWidth-size || j == winHeight-size)
        newObject(&(bbm->blocks), i, j);
      /* Otherwise we create a floor */
      else
        newObject(&(bbm->floors), i, j);
    }
  }
  /* We create the editor's toolbar */
  newObject(&(bbm->boxes), 1*size, 1*size);
  newObject(&(bbm->blocks), 3*size, 1*size);

  /* Set default tool */
  editor.tool = &bbm->blocks;

  return editor;
}

void editorLoop(Bomberman *bbm, Editor *editor){
  int mouseX, mouseY, i;
  int winWidth = MLV_get_window_width(), winHeight = MLV_get_window_height();
  /* We evaluate the marginTop */
  int marginTop = winHeight/bbm->gridSize-bbm->gridDimensions.y;
  /* We store the mouse position into mouseX and mouseY variables */
  MLV_get_mouse_position(&mouseX, &mouseY);
  /*
    We check if the mouse cursor is inside the board
    (edge blocks excluded, as we don't want the user to edit those ones)
  */
  if(mouseX > bbm->gridSize && mouseX < winWidth-bbm->gridSize
	 && mouseY > (1+marginTop)*bbm->gridSize && mouseY < winHeight-bbm->gridSize){
    if(!MLV_get_mouse_button_state(MLV_BUTTON_LEFT)){
      /* When left click is pressed, the user paint */
      /* Check if there is another same object here */
      for(i = 0; i < editor->tool->length; i++){
        if(mouseX/bbm->gridSize*bbm->gridSize == editor->tool->list[i].x
          && mouseY/bbm->gridSize*bbm->gridSize == editor->tool->list[i].y){
          /* if there is one, abort creation */
          return;
        }
      }
      /*
        we create a block which correspond to the selected tool at the mouse coordinates divided then multiplied by gridSize
        since they are all integers, it maps the coordinates to the grid
      */
      newObject(
        editor->tool,
        mouseX/bbm->gridSize*bbm->gridSize,
        mouseY/bbm->gridSize*bbm->gridSize
      );
    }
    if(!MLV_get_mouse_button_state(MLV_BUTTON_RIGHT)){
      /*
        If the right click is pressed,
        we loop through every block and check if the mouse is over it
        If that's the case, then we remove that block
        Also we do that loop backward because we pop out the element from the list
        Otherwise, if there were 2 neighbour blocks to remove, we would skip the second one
      */
      for(i = bbm->blocks.length-1; i >= 0 ; --i){
        if(mouseX/bbm->gridSize == bbm->blocks.list[i].x/bbm->gridSize
        && mouseY/bbm->gridSize == bbm->blocks.list[i].y/bbm->gridSize){
          deleteObject(&(bbm->blocks), i);
        }
      }
      /* The same with boxes , TODO: Change that*/
      for(i = bbm->boxes.length-1; i >= 0 ; --i){
        if(mouseX/bbm->gridSize == bbm->boxes.list[i].x/bbm->gridSize
        && mouseY/bbm->gridSize == bbm->boxes.list[i].y/bbm->gridSize){
          deleteObject(&(bbm->boxes), i);
        }
      }
    }
    /* Check if the user click in the toolbar */
  }else if(mouseY >= bbm->gridSize && mouseY < marginTop*bbm->gridSize - bbm->gridSize){
     if(!MLV_get_mouse_button_state(MLV_BUTTON_LEFT)){
      /* Check which button has been clicked and change the selected tool*/
      if(mouseX >= bbm->gridSize && mouseX <= 2*bbm->gridSize){
        editor->tool = &(bbm->boxes);
      }else if(mouseX >= 3*bbm->gridSize && mouseX <= 4*bbm->gridSize){
        editor->tool = &(bbm->blocks);
      }
    }
  }
}
