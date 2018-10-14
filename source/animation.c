#include "animation.h"

Animations *initAnimations(void){
  Animations *animations = malloc(sizeof(Animations));
  animations->length = 0;
  animations->list = NULL;
  return animations;
}

Animation *newAnimation(Animations *animations, char *filePattern, Coord *dimensions, double speed, double rotation){
  int i = 0, noMoreFile = 0;
  /*
    'fileDirectory' is where are located the sprites
    'fullPattern' is going to be the pattern 'filePattern' with '%d' replaced by incrementing integers
    'fullCurrentFile' is the concatenation of 'fileDirectory' and the 'fullPattern'
    We allocated the memory for the 'currentFile' and 'fullCurrentFile' strings
    The '+1' represents '\0' + a 2 digit number in base 10 - the '%d' chars = 1+2-2 = 1
    (therefore an animation can't have more than 99 sprites, which is way enough)
  */
  char *fileDirectory = "resources/sprites/";
  char *currentFile = malloc((strlen(filePattern)+1)*sizeof(char));
  char *fullCurrentFile = malloc((strlen(fileDirectory)+strlen(filePattern)+1)*sizeof(char));
  Animation *animation = NULL;
  /* We prepare the animation structure to be returned */
  animation = malloc(sizeof(Animation));
  animation->speed = speed;
  animation->index = 0;
  animation->list = NULL;
  /* While a next file exists, we add it to the animation->list */
  for(; !noMoreFile; ++i){
    sprintf(currentFile, filePattern, i);
    sprintf(fullCurrentFile, "%s%s", fileDirectory, currentFile);
    if(access(fullCurrentFile, F_OK) == -1)
      noMoreFile = 1;
    else{
      animation->list = realloc(animation->list, (i+1)*sizeof(MLV_Image *));
      animation->list[i] = MLV_load_image(fullCurrentFile);
      MLV_resize_image_with_proportions(animation->list[i], dimensions->x, dimensions->y);
      MLV_rotate_image(animation->list[i], rotation);
    }
  }
  animation->length = i-1;
  free(currentFile);
  free(fullCurrentFile);
  /* We add the animation in animations */
  animations->list = realloc(animations->list, (animations->length+1)*sizeof(Animation *));
  animations->list[animations->length++] = animation;
  /* Finally we return the animation */
  return animation;
}

void drawAnimation(Animation *animation, int x, int y){
  MLV_draw_image(animation->list[(int)animation->index], x, y);
  animation->index += animation->speed;
  if(animation->index >= animation->length)
    animation->index = 0;
}

void freeAnimation(Animation *animation){
  int i = 0;
  /* Loops through all the sprites of the animation to free them all */
  for(; i < animation->length; ++i)
    MLV_free_image(animation->list[i]);
  free(animation->list);
  free(animation);
}

void freeAnimations(Animations *animations){
  int i = 0;
  /* Loops through all the animations to free them */
  for(; i < animations->length; ++i)
    freeAnimation(animations->list[i]);
  /* Then frees the pseudo array itself */
  free(animations);
}
