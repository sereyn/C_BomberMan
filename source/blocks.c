#include "blocks.h"

Blocks initBlocks(MLV_Image *sprite){
	Blocks blocks;
	blocks.length = 0;
	blocks.sprite = sprite;
	blocks.size = MLV_get_image_width(sprite);
	return blocks;
}

void newBlock(Blocks *blocks, int x, int y){
	Block block;
	block.x = x;
	block.y = y;
	if(blocks->length == 0)
		blocks->list = malloc(sizeof(Block));
	else
		blocks->list = realloc(blocks->list, (blocks->length+1)*sizeof(Block));
	blocks->list[blocks->length++] = block;
}

void drawBlocks(Blocks blocks){
	int i = 0;
	for(; i < blocks.length; ++i){
		MLV_draw_image(blocks.sprite, blocks.size*blocks.list[i].x, blocks.size*blocks.list[i].y);
	}
}

void freeBlocks(Blocks blocks){
	free(blocks.list);
}
