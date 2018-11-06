#include "editor.h"

int isForbiddenBlock(int x, int y, int w, int h){
  /* We check if the block is in one of the spawn player zones */
  int part1 = (x == 1 && y == 1) || (x == 1+1 && y == 1) || (x == 1 && y == 1+1);
  int part2 = (x == w && y == 1) || (x == w-1 && y == 1) || (x == w && y == 1+1);
  int part3 = (x == 1 && y == h) || (x == 1+1 && y == h) || (x == 1 && y == h-1);
  int part4 = (x == w && y == h) || (x == w-1 && y == h) || (x == w && y == h-1);
  return part1 || part2 || part3 || part4;
}

Editor *initEditor(Bomberman *bbm){
  int i, j;
  /* We create variables for shorter and clearer code */
  int size = bbm->grid->size;
  Coord *dims = bbm->grid->dimensions;
  int marginTop = bbm->grid->marginTop;
  Editor *editor = malloc(sizeof(Editor));
  /* Initialise the item list */
  editor->items = malloc(sizeof(Items));
  editor->items->length = 3;
  editor->items->list = malloc(editor->items->length*sizeof(Objects *));
  /* Feeds the item list with the available items */
  editor->items->list[0] = bbm->blocks;
  editor->items->list[1] = bbm->boxes;
  editor->items->list[2] = bbm->spikes;
  /* Sets the default item */
  editor->items->current = 0;
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
  /* We create the editor's toolbar */
  for(i = 0; i < editor->items->length; ++i)
    newObject(editor->items->list[i], newCoord((2*i+1)*size, size));
  return editor;
}

void editorLoop(Editor *editor, Bomberman *bbm){
  int mouseX, mouseY, i, j;
  /* We create variables for shorter and clearer code */
  int size = bbm->grid->size;
  Coord *dims = bbm->grid->dimensions;
  int marginTop = bbm->grid->marginTop;
  /* We draw the arrow on top of the selected item */
  drawSprite(bbm->sprArrow, (2*editor->items->current+1)*size, 0, 0);
  /* We draw the informative text */
  MLV_draw_text_with_font(
    dims->x/2*size,
    size*.02,
    "~ LEVEL EDITOR ~", bbm->font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(
    (dims->x/2-3)*size,
    size*1,
    "Maintain [SHIFT] to create multiple blocks.", bbm->font, MLV_COLOR_WHITE);
  MLV_draw_text_with_font(
    (dims->x/2-2.2)*size,
    size*2,
    "Press [CTRL+S] to save your level.", bbm->font, MLV_COLOR_WHITE);
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
  && mouseY > marginTop && mouseY < marginTop+dims->y-1
  && !isForbiddenBlock(mouseX, mouseY-marginTop, dims->x-2, dims->y-2)){
    /* We check if the mouse buttons are just down, or down while shift is pressed */
    if(((isDown(bbm->inputs->lshift) || isDown(bbm->inputs->rshift))
    && (isDown(bbm->inputs->lclick) || isDown(bbm->inputs->rclick)))
    || (isJustDown(bbm->inputs->lclick) || isJustDown(bbm->inputs->rclick))){
      /*
        We remove every object under the mouse position
        For that purpose, we loop through every items,
        then through every instance of this item and check if the mouse is over it
        Also we do that loop backward because we pop out the element from the list
        Otherwise, if there were 2 neighbour items to remove, we would skip the second one
      */
      for(j = 0; j < editor->items->length; ++j){
        for(i = editor->items->list[j]->length-1; i >= 0 ; --i){
          if(mouseX == editor->items->list[j]->list[i]->position->x/size
          && mouseY == editor->items->list[j]->list[i]->position->y/size){
            deleteObject(editor->items->list[j]->list[i]);
            debug(1, "Deleted item:\nx=%d\ny=%d\nNumber of this item=%d\n\n",
              mouseX, mouseY, editor->items->list[j]->length);
          }
        }
      }
      if(isDown(bbm->inputs->lclick)){
        /* We create a block which corresponds to the selected tool at the mouse coordinates */
        newObject(editor->items->list[editor->items->current], newCoord(mouseX*size, mouseY*size));
        debug(1, "New item:\nx=%d\ny=%d\nNumber of this item=%d\n\n",
          mouseX, mouseY, editor->items->list[editor->items->current]->length);
      }
    }
  }
  /* We check if the user clicks in the toolbar */
  if(mouseY == 1){
    if(isJustDown(bbm->inputs->lclick)){
      /* Loop through all the items to check if it has been clicked and change the current item */
      for(i = 0; i < editor->items->length; ++i){
        if(mouseX == 2*i+1)
          editor->items->current = i;
      }
    }
  }
  /* We check if the user pressed ctrl+S */
  if((isDown(bbm->inputs->lctrl) || isDown(bbm->inputs->rctrl)) && isJustDown(bbm->inputs->s)){
    saveLevel(bbm);
  }
}

void freeEditor(Editor **editor){
  /* We make it being a pointer of pointer so that we can set it to point on NULL */
  if(*editor){
    free((*editor)->items->list);
    free((*editor)->items);
    free(*editor);
    *editor = NULL;
  }
}
