#include "sprites.h"

void drawSprite(Sprite *sprite, int x, int y, int index){
  MLV_draw_image(sprite->list[index], x, y);
}

void freeSprite(Sprite *sprite){
  int i = 0;
  /* Loops through all the images of the sprite to free them all */
  for(; i < sprite->length; ++i)
    MLV_free_image(sprite->list[i]);
  free(sprite->list);
  free(sprite->dimensions);
  free(sprite);
}

Sprites *initSprites(void){
  Sprites *sprites = malloc(sizeof(Sprite));
  sprites->length = 0;
  sprites->list = NULL;
  return sprites;
}

Sprite *newSprite(Sprites *sprites, char *filePattern, Coord *dimensions, double rotation){
  int i = 0, noMoreFile = 0;
  /*
    'fileDirectory' is where are located the images
    'fullPattern' is going to be the pattern 'filePattern' with '%d' replaced by incrementing integers
    'fullCurrentFile' is the concatenation of 'fileDirectory' and the 'fullPattern'
    We allocated the memory for the 'currentFile' and 'fullCurrentFile' strings
    The '+1' represents '\0' + a 2 digit number in base 10 - the '%d' chars = 1+2-2 = 1
    (therefore a sprite can't have more than 99 images, which is in our case way enough)
  */
  char *fileDirectory = "resources/sprites/";
  char *currentFile = malloc((strlen(filePattern)+1)*sizeof(char));
  char *fullCurrentFile = malloc((strlen(fileDirectory)+strlen(filePattern)+1)*sizeof(char));
  Sprite *sprite = NULL;
  /* We prepare the sprite structure to be returned */
  sprite = malloc(sizeof(Sprite));
  sprite->list = NULL;
  /* While a next file exists, we add it to the sprite->list */
  for(; !noMoreFile; ++i){
    sprintf(currentFile, filePattern, i);
    sprintf(fullCurrentFile, "%s%s", fileDirectory, currentFile);
    if(access(fullCurrentFile, F_OK) == -1)
      noMoreFile = 1;
    else{
      sprite->list = realloc(sprite->list, (i+1)*sizeof(MLV_Image *));
      sprite->list[i] = MLV_load_image(fullCurrentFile);
      MLV_resize_image_with_proportions(sprite->list[i], dimensions->x, dimensions->y);
      MLV_rotate_image(sprite->list[i], rotation);
    }
  }
  sprite->length = i-1;
  free(currentFile);
  free(fullCurrentFile);
  sprite->dimensions = newCoord(dimensions->x, dimensions->y);
  /* We add the sprite in sprites */
  sprites->list = realloc(sprites->list, (sprites->length+1)*sizeof(Sprite *));
  sprites->list[sprites->length++] = sprite;
  /* Finally we return the sprite */
  return sprite;
}

void freeSprites(Sprites *sprites){
  int i = 0;
  /* Loops through all the sprites to free them */
  for(; i < sprites->length; ++i)
    freeSprite(sprites->list[i]);
  /* Then frees the pseudo array itself */
  free(sprites);
}
