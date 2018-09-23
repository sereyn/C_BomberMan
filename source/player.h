#ifndef PLAYER
#define PLAYER

#include <MLV/MLV_all.h>

typedef struct {
	/* Pixel position */
	int x;
	int y;
	int test;
	/* Speed in px/frame */
	int speed;
} Player;

Player newPlayer();

void updatePlayer(Player *player);

#endif /* PLAYER */
