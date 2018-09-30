#include "sprites.h"

Sprites *initSprites(){
  Sprites *sprites = malloc(sizeof(Sprites));
  sprites->length = 0;
  sprites->list = NULL;
  return sprites;
}

MLV_Image *newSprite(Sprites *sprites, char *fileName, int width, int height){
  char path[50];
  MLV_Image *sprite;
  /*
    We put "resources/sprites/" in path
    Then we concat the fileName suffix and use path to load the sprite
    Finally we resize it
  */
  strcpy(path, "resources/sprites/");
  strcat(path, fileName);
  sprite = MLV_load_image(path);
  MLV_resize_image_with_proportions(sprite, width, height);
  /*
    We ask for 1 more slot of memory for our list to save the new sprite
    Then we save that sprite at the end of the list and increment the length
  */
  sprites->list = realloc(sprites->list, (sprites->length+1)*sizeof(MLV_Image *));
  sprites->list[sprites->length++] = sprite;
  return sprite;
}

void freeSprites(Sprites *sprites){
  /* Loops through all the sprites to free them */
  int i = 0;
  for(; i < sprites->length; ++i)
    MLV_free_image(sprites->list[i]);
  /* Then frees the array itself */
  free(sprites->list);
}
