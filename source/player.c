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
  player->size = bbm->grid->size*4/5;
  /* We set the default position of the player according to its number */
  if(number == 1 || number == 3)
    x = bbm->grid->dimensions->x-2;
  if(number == 2 || number == 3)
    y = bbm->grid->dimensions->y-2;
  /* We fit the player's position according to the grid */
  x *= bbm->grid->size;
  y += bbm->grid->marginTop;
  y *= bbm->grid->size;
  /* We place the player at the center of its spawn case */
  x += (bbm->grid->size-player->size)/2;
  y += (bbm->grid->size-player->size)/2;
  player->position = malloc(sizeof(Coord));
  player->position->x = x;
  player->position->y = y;
  /*
    We use a speed relative to the grid's size so that we can change it without altering its apparent speed
    However, since it is forced to be an integer, it can look different if we choose a too small grid size
  */
  player->speed = 3*bbm->grid->size/40;
  /* We give it its color */
  player->color = allColors[number];
  /* We choose the right controls for the player depending of its number */
  switch(number){
    case 0:
      player->up = bbm->inputs->up;
      player->left = bbm->inputs->left;
      player->down = bbm->inputs->down;
      player->right = bbm->inputs->right;
      player->action = bbm->inputs->rshift;
      break;
    case 1:
      player->up = bbm->inputs->z;
      player->left = bbm->inputs->q;
      player->down = bbm->inputs->s;
      player->right = bbm->inputs->d;
      player->action = bbm->inputs->e;
      break;
    case 2:
      player->up = bbm->inputs->o;
      player->left = bbm->inputs->k;
      player->down = bbm->inputs->l;
      player->right = bbm->inputs->m;
      player->action = bbm->inputs->p;
      break;
    case 3:
      player->up = bbm->inputs->g;
      player->left = bbm->inputs->v;
      player->down = bbm->inputs->b;
      player->right = bbm->inputs->n;
      player->action = bbm->inputs->h;
      break;
  }
  return player;
}

int playerCollides(Player *player, int x, int y, Bomberman *bbm){
  int j, i, xColl, yColl;
  /*
    (x1, y1) is the top left coordinate of the player
    (x2, y2) is its bottom right one
  */
  int x1 = x, y1 = y;
  int x2 = x1+player->size, y2 = y1+player->size;
  /* Same goes fot the object coordinates */
  int objX1, objY1, objX2, objY2;
  /* Loop through all the objects */
  Objects *objList[3];
  objList[0] = bbm->blocks;
  objList[1] = bbm->boxes;
  objList[2] = bbm->spikes;
  for(j = 0; j < 3; ++j){
    for(i = 0; i < objList[j]->length; ++i){
      objX1 = objList[j]->list[i]->x;
      objY1 = objList[j]->list[i]->y;
      objX2 = objX1+bbm->grid->size, objY2 = objY1+bbm->grid->size;
      /* xColl is the horizontal collision, yColl is the vertical one */
      xColl = x1 < objX2 && objX1 < x2;
      yColl = y1 < objY2 && objY1 < y2;
      /* If the player collides both horizontally and vertically, we return 1 */
      if(xColl && yColl)
        return 1;
    }
  }
  return 0;
}

void movePlayer(Player *player, Bomberman *bbm){
  /*
    We sum up the right and left key's state and substract them in a way that the results equals
    1 if only right is pressed
    -1 if only left is pressed
    0 otherwise
    The same logic is applied to the vertical movement
  */
  int xSpeed = isDown(player->right)-isDown(player->left);
  int ySpeed = isDown(player->down)-isDown(player->up);
  /* Then we multiply that value by a factor player->speed to move faster than a pixel per frame */
  xSpeed *= player->speed;
  ySpeed *= player->speed;

  /*
    Horizontal movement
    We check if the player would collide in its next position
  */
  if(playerCollides(player, player->position->x+xSpeed, player->position->y, bbm)){
    /*
      If the player would collide if we simply iterate its x position by xSpeed,
      we instead increase its position pixel per pixel until it collides one pixel later
    */
    while(!playerCollides(player, player->position->x+sign(xSpeed), player->position->y, bbm))
      player->position->x += sign(xSpeed);
    /* Then we set its xSpeed to 0 */
    xSpeed = 0;
  }
  /* We can now safely iterate the player x's position by xSpeed */
  player->position->x += xSpeed;

  /*
    Vertical movement
    We apply the same logic as with the horizontal movement
  */
  if(playerCollides(player, player->position->x, player->position->y+ySpeed, bbm)){
    while(!playerCollides(player, player->position->x, player->position->y+sign(ySpeed), bbm))
      player->position->y += sign(ySpeed);
    ySpeed = 0;
  }
  player->position->y += ySpeed;
}

void drawPlayer(Player *player){
  /* Renders the player */
  MLV_draw_filled_rectangle(
    player->position->x,
    player->position->y,
    player->size,
    player->size,
    player->color
  );
}

void updatePlayer(Player *player, Bomberman *bbm){
  /* First moves the player, then draws it */
  movePlayer(player, bbm);
  drawPlayer(player);
}

void freePlayer(Player *player){
  /* Frees all the allocated memory the player knows about */
  free(player->position);
  free(player);
}
