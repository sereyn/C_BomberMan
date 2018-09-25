#include "sprites.h"

Sprites initSprites(){
  Sprites sprites;
  sprites.length = 0;
  return sprites;
}

MLV_Image *newSprite(Sprites *sprites, char *fileName, int width, int height){
  char path[50];
  MLV_Image *sprite;
  strcpy(path, "resources/sprites/");
  strcat(path, fileName);
  sprite = MLV_load_image(path);
  MLV_resize_image_with_proportions(sprite, width, height);
  if(sprites->length == 0)
    sprites->list = malloc(sizeof(*(sprites->list)));
  else
    sprites->list = realloc(sprites->list, (sprites->length+1)*sizeof(*(sprites->list)));
  sprites->list[sprites->length++] = sprite;
  return sprite;
}

void freeSprites(Sprites sprites){
  int i = 0;
  for(; i < sprites.length; ++i)
    MLV_free_image(sprites.list[i]);
  free(sprites.list);
}
