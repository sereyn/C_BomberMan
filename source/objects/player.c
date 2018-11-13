#include "player.h"
#include "../bomberman.h"

void initPlayer(int index, void *bbmVoid){
  Bomberman *bbm = bbmVoid;
  Object *player = bbm->players->list[index];
  int x = 1, y = 1;
  PlayerVars *playerVars = malloc(sizeof(PlayerVars));
  playerVars->number = index;
  playerVars->bombThrown = 0;
  playerVars->bombMax = 1;
  playerVars->flameLength = 1;
  /* We set the default position of the player according to its number */
  if(index == 1 || index == 3)
    x = bbm->grid->dimensions->x-2;
  if(index == 2 || index == 3)
    y = bbm->grid->dimensions->y-2;
  /* We fit the player's position according to the grid */
  x *= bbm->grid->size;
  y += bbm->grid->marginTop;
  y *= bbm->grid->size;
  player->position->x = x;
  player->position->y = y;
  /*
    We use a speed relative to the grid's size so that we can change it without altering its apparent speed
    However, since it is forced to be an integer, it can look different if we choose a too small grid size
  */
  playerVars->speed = 2.*((double)bbm->grid->size)/40.;
  switch(index){
    case 0:
      playerVars->up = bbm->inputs->up;
      playerVars->left = bbm->inputs->left;
      playerVars->down = bbm->inputs->down;
      playerVars->right = bbm->inputs->right;
      playerVars->action = bbm->inputs->rshift;
      break;
    case 1:
      playerVars->up = bbm->inputs->z;
      playerVars->left = bbm->inputs->q;
      playerVars->down = bbm->inputs->s;
      playerVars->right = bbm->inputs->d;
      playerVars->action = bbm->inputs->e;
      break;
    case 2:
      playerVars->up = bbm->inputs->o;
      playerVars->left = bbm->inputs->k;
      playerVars->down = bbm->inputs->l;
      playerVars->right = bbm->inputs->m;
      playerVars->action = bbm->inputs->p;
      break;
    case 3:
      playerVars->up = bbm->inputs->g;
      playerVars->left = bbm->inputs->v;
      playerVars->down = bbm->inputs->b;
      playerVars->right = bbm->inputs->n;
      playerVars->action = bbm->inputs->h;
      break;
  }
  playerVars->sprites[0] = bbm->sprPlayerRight[index];
  playerVars->sprites[1] = bbm->sprPlayerDown[index];
  playerVars->sprites[2] = bbm->sprPlayerLeft[index];
  playerVars->sprites[3] = bbm->sprPlayerUp[index];
  player->variables = playerVars;
  player->sprite = playerVars->sprites[1];
  player->sprSpeed = .1;
}

/*
  Returns if whether or not a player is colliding with an object at the 'position' coordinates
  (blocks, boxes or spikes)
*/
int playerCollides(Object *player, Bomberman *bbm){
  int j, i, xColl, yColl;
  /*
    (x1, y1) is the top left coordinate of the player
    (x2, y2) is its bottom right one
  */
  int x1 = player->position->x, y1 = player->position->y;
  int x2 = x1+bbm->grid->size, y2 = y1+bbm->grid->size;
  /* Same goes fot the object coordinates */
  int objX1, objY1, objX2, objY2;
  /* Loop through all the objects */
  Objects *objList[3];
  objList[0] = bbm->blocks;
  objList[1] = bbm->boxes;
  objList[2] = bbm->spikes;
  for(j = 0; j < 3; ++j){
    for(i = 0; i < objList[j]->length; ++i){
      objX1 = objList[j]->list[i]->position->x;
      objY1 = objList[j]->list[i]->position->y;
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

void movePlayer(Object *player, Bomberman *bbm){
  PlayerVars *playerVars = player->variables;
  int x0, y0, i = 0, minDistance = 0;
  int distance[8] = {0};
  int direction;
  /*
    We sum up the right and left key's state and substract them in a way that the results equals
    1 if only right is pressed
    -1 if only left is pressed
    0 otherwise
    The same logic is applied to the vertical movement
  */
  double xSpeed = (double)(isDown(playerVars->right)-isDown(playerVars->left));
  double ySpeed = (double)(isDown(playerVars->down)-isDown(playerVars->up));
  if(xSpeed != 0 || ySpeed != 0){
    direction = round(2.*atan2(ySpeed, xSpeed)/3.14);
    while(direction < 0)
      direction += 4;
    player->sprite = playerVars->sprites[direction%4]; 
  }else
    player->sprIndex = 0;
  /* Then we multiply that value by a factor player->speed to move faster than a pixel per frame */
  xSpeed *= playerVars->speed;
  ySpeed *= playerVars->speed;
  /* We move the player accordingly to its speeds */
  player->position->x += (int)xSpeed;
  player->position->y += (int)ySpeed;
  /* Collision check */
  if(playerCollides(player, bbm)){
    /* We are in a wall, what direction is the shortest to quit the collision? */
    x0 = player->position->x;
    y0 = player->position->y;
    for(; i < 8; ++i){
      while(playerCollides(player, bbm)){
        /*
          We move in that direction while it collides
          and increment the distance in that direction.
          1.57 is an approximation of PI/4
        */
        player->position->x += round(cos((double)i*.79));
        player->position->y += round(sin((double)i*.79));
        distance[i]++;
      }
      /*
        If the current distance is strictly lower that the previous min distance
        OR if it's equal but the current one is not diagonal,
        we set the minDistance to the current one
      */
      if(distance[i] < distance[minDistance]
      || (distance[i] == distance[minDistance] && i%2 == 0))
        minDistance = i;
      /* We reposition the player where it collided to check other directions */
      player->position->x = x0;
      player->position->y = y0;
    }
    /* Now we can finally move 'distance' steps in the best direction */
    player->position->x += round(cos((double)minDistance*.79))*distance[minDistance];
    player->position->y += round(sin((double)minDistance*.79))*distance[minDistance];
  }
}

void attackPlayer(Object *player, Bomberman *bbm){
  PlayerVars *playerVars = player->variables;
  BombVars *bombVars;
  int size = bbm->grid->size;
  Object *bomb;
  int x, y;
  if(isJustDown(playerVars->action) && playerVars->bombThrown < playerVars->bombMax){
    x = player->position->x;
    y = player->position->y;
    /* We resize the bomb at the center of its ceil */
    x = (x+size/2)/size*size;
    y = (y+size/2)/size*size;
    /* We create a bomb and set its player variable to the player number */
    bomb = newObject(bbm->bombs, newCoord(x, y));
    bombVars = bomb->variables;
    bombVars->player = playerVars->number;
    playerVars->bombThrown++;
  }
}

void updatePlayer(int index, void *bbmVoid){
  Bomberman *bbm = bbmVoid;
  Object *player = bbm->players->list[index];
  movePlayer(player, bbm);
  attackPlayer(player, bbm);
}
