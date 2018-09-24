#include "floors.h"

Floors initFloors(MLV_Image *sprite){
	Floors floors;
	floors.length = 0;
	floors.sprite = sprite;
	floors.size = MLV_get_image_width(sprite);
	return floors;
}

void newFloor(Floors *floors, int x, int y){
	Coord position;
	position.x = x;
	position.y = y;
	if(floors->length == 0)
		floors->list = malloc(sizeof(Coord));
	else
		floors->list = realloc(floors->list, (floors->length+1)*sizeof(Coord));
	floors->list[floors->length++] = position;
}

void drawFloors(Floors floors){
	int i = 0;
	for(; i < floors.length; ++i){
		MLV_draw_image(floors.sprite, floors.size*floors.list[i].x, floors.size*floors.list[i].y);
	}
}

void freeFloors(Floors floors){
	free(floors.list);
}
