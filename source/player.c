#include "player.h"

Player *newPlayer(Bomberman *bbm, int number){
  /* Here we create a new player */
  int x = 1, y = 1;
  /* This is the list of the four colors the player can have */
  MLV_Color allColors[4] = {
    MLV_COLOR_RED,
    MLV_COLOR_GREEN,
    MLV_COLOR_BLUE,
    MLV_COLOR_YELLOW
  };
  Player *player = malloc(sizeof(Player));
  player->size = bbm->grid->size;
  /* We set the default position of the player according to its number */
  if(number == 1 || number == 3)
    x = bbm->grid->dimensions->x-2;
  if(number == 2 || number == 3)
    y = bbm->grid->dimensions->y-2;
  /* We fit the player's position according to the grid */
  x *= player->size;
  y += bbm->grid->marginTop;
  y *= player->size;
  player->position = malloc(sizeof(Coord));
  player->position->x = x;
  player->position->y = y;
  player->speed = 3;
  /* We give it its color */
  player->color = allColors[number];
  /* We chooses the right controls for the player depending of its number */
  switch(number){
    case 0:
      player->up = bbm->inputs->up;
      player->left = bbm->inputs->left;
      player->down = bbm->inputs->down;
      player->right = bbm->inputs->right;
      break;
    case 1:
      player->up = bbm->inputs->z;
      player->left = bbm->inputs->q;
      player->down = bbm->inputs->s;
      player->right = bbm->inputs->d;
      break;
    case 2:
      player->up = bbm->inputs->o;
      player->left = bbm->inputs->k;
      player->down = bbm->inputs->l;
      player->right = bbm->inputs->m;
      break;
    case 3:
      player->up = bbm->inputs->g;
      player->left = bbm->inputs->v;
      player->down = bbm->inputs->b;
      player->right = bbm->inputs->n;
      break;
  }
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
  int xSpeed = isDown(player->right)-isDown(player->left);
  int ySpeed = isDown(player->down)-isDown(player->up);
  /* We then move the player with a speed factor */
  player->position->x += player->speed*xSpeed;
  player->position->y += player->speed*ySpeed;
  /* Renders the player */
  MLV_draw_filled_rectangle(player->position->x, player->position->y,
    player->size, player->size, player->color);
}

void freePlayer(Player *player){
  free(player->position);
  free(player);
}
