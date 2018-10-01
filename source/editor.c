#include "editor.h"

void newItem(Items *items, Objects *item){
  /*
    Increase the items length and capacity
    Then sets its new free place to the desired new item
  */
  items->list = realloc(items->list, (++items->length)*sizeof(Objects *));
  items->list[items->length-1] = item;
}

Editor *initEditor(Bomberman *bbm){
  Editor *editor = malloc(sizeof(Editor));
  int i, j;
  /* We create variables for shorter and clearer code */
  int size = bbm->grid->size;
  Coord *dims = bbm->grid->dimensions;
  int marginTop = bbm->grid->marginTop;
  /* We loop through the whole board */
  debug(1, "Filling the editor grid\n");
  for(i = 0; i < dims->x; ++i){
    for(j = 0; j < dims->y; ++j){
      /* If we are at the edge of the board, we create a block */
      if(i == 0 || j == 0
      || i == dims->x-1 || j == dims->y-1)
        newObject(bbm->blocks, newCoord(i*size, (j+marginTop)*size));
      /* Otherwise we create a floor */
      else
        newObject(bbm->floors, newCoord(i*size, (j+marginTop)*size));
    }
  }

  /* Initialise the item list */
  editor->items = malloc(sizeof(Items));
  editor->items->length = 0;
  editor->items->list = NULL;
  /* Feeds the item list with the available items */
  newItem(editor->items, bbm->blocks);
  newItem(editor->items, bbm->boxes);
  newItem(editor->items, bbm->spikes);
  /* Sets the default item */
  editor->items->current = editor->items->list[0];
  /* We create the editor's toolbar */
  for(i = 0; i < editor->items->length; ++i)
    newObject(editor->items->list[i], newCoord((2*i+1)*size, size));
  return editor;
}

void editorLoop(Editor *editor, Bomberman *bbm){
  int mouseX, mouseY, i, j;
  int leftPressed = !MLV_get_mouse_button_state(MLV_BUTTON_LEFT);
  int rightPressed = !MLV_get_mouse_button_state(MLV_BUTTON_RIGHT);
  /* We create variables for shorter and clearer code */
  int size = bbm->grid->size;
  Coord *dims = bbm->grid->dimensions;
  int marginTop = bbm->grid->marginTop;
  /*
    We store the mouse position into mouseX and mouseY variables
    Also we divide them by size so that it maps to the grid
  */
  MLV_get_mouse_position(&mouseX, &mouseY);
  mouseX /= size;
  mouseY /= size;
  /*
    We check if the mouse cursor is inside the board
    (edge blocks excluded, as we don't want the user to edit those ones)
  */
  if(mouseX > 0 && mouseX < dims->x-1
	 && mouseY > marginTop && mouseY < marginTop+dims->y-1){
    if(leftPressed || rightPressed){
      /*
        We remove every object under the mouse position
        For that purpose, we loop through every items,
        then through every instance of this item and check if the mouse is over it
        Also we do that loop backward because we pop out the element from the list
        Otherwise, if there were 2 neighbour items to remove, we would skip the second one
      */
      for(j = 0; j < editor->items->length; ++j){
        for(i = editor->items->list[j]->length-1; i >= 0 ; --i){
          if(mouseX == editor->items->list[j]->list[i]->x/size
          && mouseY == editor->items->list[j]->list[i]->y/size){
            deleteObject(editor->items->list[j], i);
            debug(1, "Deleted item:\nx=%d\ny=%d\nNumber of this item=%d\n\n",
              mouseX, mouseY, editor->items->list[j]->length);
          }
        }
      }
      if(leftPressed){
        /* We create a block which corresponds to the selected tool at the mouse coordinates */
        newObject(editor->items->current, newCoord(mouseX*size, mouseY*size));
        debug(1, "New item:\nx=%d\ny=%d\nNumber of this item=%d\n\n",
          mouseX, mouseY, editor->items->current->length);
      }
    }
  }
  /*
    We check if the user clicks in the toolbar
  */
  if(mouseY == 1){
    if(leftPressed){
      /* Loop through all the items to check if it has been clicked and change the current item */
      for(i = 0; i < editor->items->length; ++i){
        if(mouseX == 2*i+1)
          editor->items->current = editor->items->list[i];
      }
    }
  }
}

void freeEditor(Editor *editor){
  free(editor->items->list);
  free(editor->items);
  free(editor);
}
