#include <MLV/MLV_all.h>
#include "utils.h"
#include "bomberman.h"
#include "game.h"
#include "editor.h"
#include "grid.h"
#include "inputs.h"

/*
  exitCallback's prototype must be void fun(void *)
  It is called whenever the player closes the game using the cross button
*/
void exitCallback(void *data){
  /*
    We convert data's type to int* and save this pointer into closed
    Then we change the value of closed to 1
  */
  int *closed = (int*) data;
  *closed = 1;
}

int main(void){
  int closed = 0;
  /* Creates a grid of 40px per block, dimensions 21x13 and a marginTop of 3*/
  Grid *grid = initGrid(40, newCoord(21, 13), 3);
  Bomberman *bomberman;
  Game *game;
  Editor *editor;
  debug(0, "Loading...\n");
  /* We call an MLV function which takes a callback meant to switch closed to 1 */
  MLV_execute_at_exit(exitCallback, &closed);
  /*
    We create the game window with the grid's dimensions
    Then we set its frame rate to 60
  */
  MLV_create_window("Bomberman", "Bomberman",
    grid->size*grid->dimensions->x,
    grid->size*(grid->dimensions->y+grid->marginTop)
  );
  MLV_change_frame_rate(60);
  /*
    We initialise bomberman
    This has to be done after the window creation because it prepares the sprites
    (we don't need to free the grid since freeBomberman will do it for us)
  */
  bomberman = initBomberman(grid);
  /* We initialise the editor */
  /* editor = initEditor(bomberman); */
  game = initGame(bomberman);
  /*
    Game loop:
    This while keeps looping until the user presses escape or the cross button
  */
  while(!isDown(bomberman->inputs->escape) && !closed){
    MLV_clear_window(MLV_COLOR_BLACK);

    updateInputs(bomberman->inputs);
    gameLoop(game, bomberman);
    /* editorLoop(editor, bomberman); */
    drawAll(bomberman);

    MLV_actualise_window();
    MLV_delay_according_to_frame_rate();
  }
  /*
    Once the code reaches this point, the game is over
    We need to free all the memory allocated during the game process
  */
  freeGame(game);
  /* freeEditor(editor); */
  freeBomberman(bomberman);
  MLV_free_window();
  /* If that line doesn't show up, then something went wrong */
  debug(0, "Terminated successfully\n");
  exit(EXIT_SUCCESS);
}
