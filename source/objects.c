#include "objects.h"

Objects initObjects(MLV_Image *sprite){
  Objects objects;
  objects.length = 0;
  objects.sprite = sprite;
  objects.dimensions.x = MLV_get_image_width(sprite);
  objects.dimensions.y = MLV_get_image_height(sprite);
  return objects;
}

void newObject(Objects *objects, int x, int y){
  Coord position;
  position.x = x;
  position.y = y;
  if(objects->length == 0)
    objects->list = malloc(sizeof(*(objects->list)));
  else
    objects->list = realloc(objects->list, (objects->length+1)*sizeof(*(objects->list)));
  objects->list[objects->length++] = position;
}

void deleteObject(Objects *objects, int index){
  int i = index;
  if(index < 0 || index >= objects->length)
    exit(EXIT_FAILURE);
  for(; i < objects->length-1; ++i)
    objects->list[i] = objects->list[i+1];
  objects->list = realloc(objects->list, (--objects->length)*sizeof(*(objects->list)));
}

void drawObjects(Objects objects){
  int i = 0;
  for(; i < objects.length; ++i){
    MLV_draw_image(
      objects.sprite,
      objects.dimensions.x*objects.list[i].x,
      objects.dimensions.y*objects.list[i].y
    );
  }
}

void freeObjects(Objects objects){
  free(objects.list);
}
