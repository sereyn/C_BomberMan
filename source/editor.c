#include "editor.h"

Editor *initEditor(Bomberman *bbm){
  Editor *editor = malloc(sizeof(Editor));
  int i, j;
  int winWidth = MLV_get_window_width(), winHeight = MLV_get_window_height();
  /* We let size be bbm->grid->size for shorter and clearer code */
  int size = bbm->grid->size;
  /*
    We evaluate the marginTop
    It represents the number of blocks to skip at the top of the grid
  */
  int marginTop = winHeight/bbm->grid->size-bbm->grid->dimensions->y;
  /* We loop through the whole board */
  debug(1, "Filling the editor grid\n");
  for(i = 0; i < winWidth; i += size){
    for(j = marginTop*size; j < winHeight; j += size){
      /* If we are at the edge of the board, we create a block */
      if(i == 0 || j == marginTop*size
      || i == winWidth-size || j == winHeight-size)
        newObject(bbm->blocks, newCoord(i, j));
      /* Otherwise we create a floor */
      else
        newObject(bbm->floors, newCoord(i, j));
    }
  }
  /* We create the editor's toolbar */
  newObject(bbm->boxes, newCoord(1*size, 1*size));
  newObject(bbm->blocks, newCoord(3*size, 1*size));

  /* Set default tool */
  editor->item = bbm->blocks;

  return editor;
}

void editorLoop(Bomberman *bbm, Editor *editor){
  int mouseX, mouseY, i;
  int winWidth = MLV_get_window_width(), winHeight = MLV_get_window_height();
  /* We evaluate the marginTop */
  int marginTop = winHeight/bbm->grid->size-bbm->grid->dimensions->y;
  /* We store the mouse position into mouseX and mouseY variables */
  MLV_get_mouse_position(&mouseX, &mouseY);
  /*
    We check if the mouse cursor is inside the board
    (edge blocks excluded, as we don't want the user to edit those ones)
  */
  if(mouseX > bbm->grid->size && mouseX < winWidth-bbm->grid->size
	 && mouseY > (1+marginTop)*bbm->grid->size && mouseY < winHeight-bbm->grid->size){
    if(!MLV_get_mouse_button_state(MLV_BUTTON_LEFT)){
      /*
        When left click is pressed, the user paints
        Check if there is another same object here
      */
      for(i = 0; i < editor->item->length; i++){
        if(mouseX/bbm->grid->size*bbm->grid->size == editor->item->list[i]->x
          && mouseY/bbm->grid->size*bbm->grid->size == editor->item->list[i]->y){
          /* If there is one, abort creation */
          return;
        }
      }
      /*
        we create a block which corresponds to the selected tool at the mouse coordinates divided then multiplied by grid->size
        since they are all integers, it maps the coordinates to the grid
      */
      newObject(editor->item, newCoord(
        mouseX/bbm->grid->size*bbm->grid->size,
        mouseY/bbm->grid->size*bbm->grid->size
      ));
      debug(1, "New item:\nx=%d\ny=%d\nNumber of this item=%d\n\n",
        mouseX/bbm->grid->size,
        mouseY/bbm->grid->size,
        editor->item->length
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
      for(i = bbm->blocks->length-1; i >= 0 ; --i){
        if(mouseX/bbm->grid->size == bbm->blocks->list[i]->x/bbm->grid->size
        && mouseY/bbm->grid->size == bbm->blocks->list[i]->y/bbm->grid->size){
          deleteObject(bbm->blocks, i);
          debug(1, "Deleted item:\nx=%d\ny=%d\nNumber of this item=%d\n\n",
            mouseX/bbm->grid->size,
            mouseY/bbm->grid->size,
            bbm->blocks->length
          );
        }
      }
      /* The same with boxes , TODO: Change that*/
      for(i = bbm->boxes->length-1; i >= 0 ; --i){
        if(mouseX/bbm->grid->size == bbm->boxes->list[i]->x/bbm->grid->size
        && mouseY/bbm->grid->size == bbm->boxes->list[i]->y/bbm->grid->size){
          deleteObject(bbm->boxes, i);
          debug(1, "Deleted item:\nx=%d\ny=%d\nNumber of this item=%d\n\n",
            mouseX/bbm->grid->size,
            mouseY/bbm->grid->size,
            bbm->boxes->length
          );
        }
      }
    }
    /* Check if the user click in the toolbar */
  }else if(mouseY >= bbm->grid->size && mouseY < marginTop*bbm->grid->size - bbm->grid->size){
     if(!MLV_get_mouse_button_state(MLV_BUTTON_LEFT)){
      /* Check which button has been clicked and change the selected tool*/
      if(mouseX >= bbm->grid->size && mouseX <= 2*bbm->grid->size){
        editor->item = bbm->boxes;
      }else if(mouseX >= 3*bbm->grid->size && mouseX <= 4*bbm->grid->size){
        editor->item = bbm->blocks;
      }
    }
  }
}
