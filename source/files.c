#include "files.h"

void saveFile(){
	FILE *level = fopen("level", "wb");
	if(!level)
		exit(EXIT_FAILURE);
	/* To be continued */
	fclose(level);
}

void loadFile(){
	FILE *level = fopen("level", "rd");
	if(!level)
		exit(EXIT_FAILURE);
	/* To be continued */
	fclose(level);
}