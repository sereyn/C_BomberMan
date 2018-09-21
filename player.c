#include "player.h"

Player newPlayer(){
  Player player;
  player.x = 50;
  player.y = 10;
  player.speed = 125;
  return player;
}

void updatePlayer(Player *player){
  float x_acceleration = player->speed*(1./(float)(FPS))*(int)(MLV_get_keyboard_state(MLV_KEYBOARD_RIGHT) - MLV_get_keyboard_state(MLV_KEYBOARD_LEFT));
  float y_acceleration = player->speed*(1./(float)(FPS))*(int)(MLV_get_keyboard_state(MLV_KEYBOARD_UP) - MLV_get_keyboard_state(MLV_KEYBOARD_DOWN));
  player->x -= (int)x_acceleration;
  player->y += (int)y_acceleration;

  MLV_draw_filled_rectangle(player->x, player->y, 50, 50, MLV_COLOR_WHITE);
}
