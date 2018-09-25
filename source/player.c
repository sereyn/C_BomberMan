#include "player.h"

Player newPlayer(){
  Player player;
  player.position.x = 50;
  player.position.y = 10;
  player.speed = 3;
  return player;
}

void updatePlayer(Player *player){
  /*
    We sum up the right and left key's state and substract them in a way that the results equals
    1 if only right is pressed
    -1 if only left is pressed
    0 otherwise
    The same logic is applied to the vertical movement
  */
  int xSpeed = MLV_get_keyboard_state(MLV_KEYBOARD_LEFT)-MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT);
  int ySpeed = MLV_get_keyboard_state(MLV_KEYBOARD_UP)-MLV_get_keyboard_state(MLV_KEYBOARD_DOWN);
  /* We then move the player with a speed factor */
  player->position.x += player->speed*xSpeed;
  player->position.y += player->speed*ySpeed;
  /* Renders the player */
  MLV_draw_filled_rectangle(player->position.x, player->position.y, 50, 50, MLV_COLOR_WHITE);
}
