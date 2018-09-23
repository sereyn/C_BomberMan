#include "sprites.h"

Sprites initSprites(){
	Sprites sprites;
	sprites.length = 0;
	return sprites;
}

MLV_Image *newSprite(Sprites *sprites, char *path, int width, int height){
	MLV_Image *sprite = MLV_load_image(path);
	MLV_resize_image_with_proportions(sprite, width, height);
	if(sprites->length == 0)
		sprites->sprites = malloc(sizeof(MLV_Image *));
	else
		sprites->sprites = realloc(sprites->sprites, (sprites->length+1)*sizeof(MLV_Image *));
	sprites->sprites[sprites->length++] = sprite;
	return sprite;
}

void freeSprites(Sprites sprites){
	int i = 0;
	for(; i < sprites.length; ++i)
		MLV_free_image(sprites.sprites[i]);
	free(sprites.sprites);
}
