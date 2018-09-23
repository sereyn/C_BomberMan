#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "player.h"
#include "files.h"
#include "blocks.h"
#include "sprites.h"

void exitCallback(void *data){
	int *closed = (int*) data;
	*closed = 1;
}

int main(void){
	/* Declare variables */
	int closed = 0;
	int gridSize = 64;

	Player player_one;

	Sprites sprites = initSprites();

	MLV_Image *sprBlock;
	Blocks blocks;

	/* Output loading */
	fprintf(stdout, "Loading...\n\n");

	/* Catches whenever the user quits the program */
	MLV_execute_at_exit(exitCallback, &closed);

	/* Initialize the window and set its FPS to 60 */
	MLV_create_window("Bomberman", "Bomberman", 800, 608);
	MLV_change_frame_rate(60);

	/* Initialize the player_one */
	player_one = newPlayer();

	/* Blocks */
	sprBlock = newSprite(&sprites, "block.png", gridSize, gridSize);
	blocks = initBlocks(sprBlock);
	newBlock(&blocks, 3, 1);
	newBlock(&blocks, 1, 3);
	newBlock(&blocks, 1, 1);
	newBlock(&blocks, 5, 6);

	/* Loop until the user quits */
	while(MLV_get_keyboard_state(MLV_KEYBOARD_ESCAPE) && !closed){
		/* Clear the window */
		MLV_clear_window(MLV_COLOR_BLACK);

		/* Update */
		updatePlayer(&player_one);
		drawBlocks(blocks);
		
		/* Show the refreshed window and wait 1/FPS seconds */
		MLV_actualise_window();
		MLV_delay_according_to_frame_rate();
	}

	/* Free the allocated space */
	freeSprites(sprites);
	freeBlocks(blocks);
	MLV_free_window();

	/* It's over (if that line doesn't show up after the execution, something went wrong) */
	fprintf(stdout, "Terminated successfully\n");
	exit(EXIT_SUCCESS);
}
