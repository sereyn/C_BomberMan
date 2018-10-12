#include "files.h"

void saveFile(Objects **allObjects, int allObjectsLength){
  int i, j;
  FILE *level = fopen("level", "w");
  if(!level)
    exit(EXIT_FAILURE);
  /* Write in file */
  for(i = 0; i < allObjectsLength; i++){
    /* A symbolic letter to identify the begining */
    fputc('~', level);
    fprintf(level, "\n");
    /* A letter to identify which block we are talking about */
    fputc(allObjects[i]->termChar, level);
    fprintf(level, "\n");
    /* Loop into the current object */
    for(j = 0; j < allObjects[i]->length; j++){
      fprintf(level, "%d;%d\n", allObjects[i]->list[j]->x, allObjects[i]->list[j]->y);
    }

  }
  fclose(level);
  debug(0, "Level saved!");
}

void loadFile(){
  FILE *level = fopen("level", "rb");
  if(!level)
    exit(EXIT_FAILURE);
  /* To be continued */
  fclose(level);
}