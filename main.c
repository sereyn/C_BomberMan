#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>

int main(int argc, char *argv[]){
  MLV_create_window("BomberMan", "testing", 500, 500);
  MLV_draw_text(250, 50, "Title screen", MLV_COLOR_WHITE);
  
  MLV_actualise_window();
  MLV_wait_seconds(10);

  MLV_free_window();
    
  exit(EXIT_SUCCESS);
}
