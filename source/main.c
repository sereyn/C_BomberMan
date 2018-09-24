#include <stdio.h>
#include <MLV/MLV_all.h>
#include "bomberman.h"
#include "editor.h"

void exitCallback(void *data){
	int *closed = (int*) data;
	*closed = 1;
}

int main(void){
	int closed = 0;
	Bomberman bomberman;

	MLV_execute_at_exit(exitCallback, &closed);
	MLV_create_window("Bomberman", "Bomberman", 40*21, 40*16);
	MLV_change_frame_rate(60);

	bomberman = initBomberman();
	initEditor(&bomberman);

	while(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) && !closed){
		MLV_clear_window(MLV_COLOR_BLACK);

		drawAll(bomberman);
		editorLoop(&bomberman);

		MLV_actualise_window();
		MLV_delay_according_to_frame_rate();
	}

	freeBomberman(bomberman);
	MLV_free_window();

	fprintf(stdout, "Terminated successfully\n");
	exit(EXIT_SUCCESS);
}
