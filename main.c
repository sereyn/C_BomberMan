#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>

int main(int argc, char *argv[]){
  int i;
  int game_running = 0;
  MLV_Keyboard_button button_pressed = MLV_KEYBOARD_UP;
  MLV_Keyboard_button buttons_listened[] = {MLV_KEYBOARD_UP, MLV_KEYBOARD_DOWN, MLV_KEYBOARD_LEFT, MLV_KEYBOARD_RIGHT};

  MLV_create_window("BomberMan - Title screen", "BomberMan", 500, 500);

  game_running = 1;
  while(game_running){
     MLV_clear_window(MLV_COLOR_BLACK);

     for(i=0; i<sizeof(buttons_listened)/sizeof(buttons_listened[0]); i++){
       if(MLV_get_keyboard_state(buttons_listened[i]) == MLV_PRESSED){
	 button_pressed = buttons_listened[i];
       }
     }
     
     MLV_draw_text(250, 250,  MLV_convert_keyboard_button_to_string(button_pressed), MLV_COLOR_WHITE);
     MLV_actualise_window();
  }

  
  exit(EXIT_SUCCESS);
}
