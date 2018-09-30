#include "utils.h"
#include <MLV/MLV_all.h>
#include "bomberman.h"
#include "editor.h"

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
  int closed = 0, gridSize = 35;
  Coord gridDimensions = {21, 13};
  Bomberman bomberman;
  Editor editor;
  debug(0, "Loading...\n");
  /* We call an MLV function which takes a callback meant to switch closed to 1 */
  MLV_execute_at_exit(exitCallback, &closed);
  /*
    We create the game window with a 21x16 grid's dimension
    Then we set its frame rate to 60
    The "+3" means there are 3 free lines at the top
  */
  MLV_create_window("Bomberman", "Bomberman",
    gridSize*gridDimensions.x,
    gridSize*(gridDimensions.y+3)
  );
  MLV_change_frame_rate(60);
  /*
    We initialise bomberman
    This has to be done after the window creation because it prepares the sprites
  */
  bomberman = initBomberman(gridSize, gridDimensions);
  /*
    Game loop:
    This while keeps looping until the user presses escape or the cross button
  */
  while(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) && !closed){
    MLV_clear_window(MLV_COLOR_BLACK);

    editorLoop(&bomberman, &editor);
    drawAll(bomberman);

    MLV_actualise_window();
    MLV_delay_according_to_frame_rate();
  }
  /*
    Once the code reaches this point, the game is over
    We need to free all the memory allocated during the game process
  */
  freeBomberman(bomberman);
  MLV_free_window();
  /* If that line doesn't show up, then something went wrong */
  debug(0, "Terminated successfully\n");
  exit(EXIT_SUCCESS);
}
