#ifndef FLOORS
#define FLOORS

#include <MLV/MLV_all.h>
#include "utils.h"

typedef struct {
	Coord *list;
	int length;
	MLV_Image *sprite;
	int size;
} Floors;

Floors initFloors(MLV_Image *sprite);

void newFloor(Floors *floors, int x, int y);

void drawFloors(Floors floors);

void freeFloors(Floors floors);

#endif /* FLOORS */