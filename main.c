#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "window.h"
#include "player.h"

int main(int argc, char *argv[]){
  int game_running = 0;
  Player player_one = newPlayer();

  printf("loading\n\n");

  MLV_create_window("BomberMan - Title screen", "BomberMan", 500, 500);
  MLV_change_frame_rate(FPS);

  game_running = 1;

  while(game_running){
     MLV_clear_window(MLV_COLOR_BLACK);

     updatePlayer(&player_one);
     
     MLV_actualise_window();
     MLV_delay_according_to_frame_rate();
  }

  
  exit(EXIT_SUCCESS);
}
