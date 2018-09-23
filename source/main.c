#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "player.h"

void exitCallback(void *data){
	int *closed = (int*) data;
	*closed = 1;
}

int main(void){
	/* Declare variables */
	int closed = 0;
	Player player_one;

	/* Output loading */
	fprintf(stdout, "Loading...\n\n");

	/* Catches whenever the user quits the program */
	MLV_execute_at_exit(exitCallback, &closed);

	/* Initialize the window and set its FPS to 60 */
	MLV_create_window("Bomberman", "Bomberman", 800, 608);
	MLV_change_frame_rate(60);

	/* Initialize the player_one */
	player_one = newPlayer();

	/* Loop until the user quits */
	while(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) && !closed){
		/* Clear the window */
		MLV_clear_window(MLV_COLOR_BLACK);

		/* Update */
		updatePlayer(&player_one);
		
		/* Show the refreshed window and wait 1/FPS seconds */
		MLV_actualise_window();
		MLV_delay_according_to_frame_rate();
	}

	/* Free the allocated space */
	MLV_free_window();

	/* It's over (if that line doesn't show up after the execution, something went wrong) */
	fprintf(stdout, "Terminated successfully\n");
	exit(EXIT_SUCCESS);
}
