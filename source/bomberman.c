#include "bomberman.h"

Bomberman initBomberman(){
  Bomberman bbm;
  bbm.gridSize = 40;
  bbm.sprites = initSprites();
  bbm.sprBlock = newSprite(&(bbm.sprites), "block.png", bbm.gridSize, bbm.gridSize);
  bbm.sprFloor = newSprite(&(bbm.sprites), "floor.png", bbm.gridSize, bbm.gridSize);
  bbm.floors = initObjects(bbm.sprFloor);
  bbm.blocks = initObjects(bbm.sprBlock);
  return bbm;
}

void drawAll(const Bomberman bbm){
  drawObjects(bbm.floors);
  drawObjects(bbm.blocks);
}

void freeBomberman(Bomberman bbm){
  freeObjects(bbm.floors);
  freeObjects(bbm.blocks);
  freeSprites(bbm.sprites);
}
