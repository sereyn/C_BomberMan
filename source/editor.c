#include "editor.h"

void initEditor(Bomberman *bbm){
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
  debug(1, "Filling the editor grid\n");
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
}

void editorLoop(Bomberman *bbm){
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
      debug(1, "New block:\nx=%d\ny=%d\nblocks' length=%d\n\n",
        mouseX/bbm->gridSize,
        mouseY/bbm->gridSize,
        bbm->blocks.length
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
          debug(1, "Deleted block:\nx=%d\ny=%d\nblocks' length=%d\n\n",
            mouseX/bbm->gridSize,
            mouseY/bbm->gridSize,
            bbm->blocks.length
          );
        }
      }
    }
  }
}
