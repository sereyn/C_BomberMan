#include "player.h"

Player newPlayer(){
  Player player;
  player.position.x = 50;
  player.position.y = 10;
  player.speed = 3;
  return player;
}

void updatePlayer(Player *player){
  /* Move the player according to the user inputs */
  int xSpeed = MLV_get_keyboard_state(MLV_KEYBOARD_LEFT)-MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT);
  int ySpeed = MLV_get_keyboard_state(MLV_KEYBOARD_UP)-MLV_get_keyboard_state(MLV_KEYBOARD_DOWN);
  player->position.x += player->speed*xSpeed;
  player->position.y += player->speed*ySpeed;

  /* Render the player */
  MLV_draw_filled_rectangle(player->position.x, player->position.y, 50, 50, MLV_COLOR_WHITE);
}
