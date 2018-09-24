#include "bomberman.h"

Bomberman initBomberman(){
	Bomberman bbm;
	bbm.gridSize = 40;
	bbm.sprites = initSprites();
	bbm.sprBlock = newSprite(&(bbm.sprites), "block.png", bbm.gridSize, bbm.gridSize);
	bbm.sprFloor = newSprite(&(bbm.sprites), "floor.png", bbm.gridSize, bbm.gridSize);
	bbm.floors = initFloors(bbm.sprFloor);
	bbm.blocks = initBlocks(bbm.sprBlock);
	return bbm;
}

void drawAll(const Bomberman bbm){
	drawFloors(bbm.floors);
	drawBlocks(bbm.blocks);
}

void freeBomberman(Bomberman bbm){
	freeFloors(bbm.floors);
	freeSprites(bbm.sprites);
	freeBlocks(bbm.blocks);
}
