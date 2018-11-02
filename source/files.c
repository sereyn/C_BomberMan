#include "files.h"

int countLevels(void){
  int fileNumber = 0;
  char *prefix = "resources/levels/lvl";
  char *suffix = ".txt";
  /*
    We alloc the needed memory to path for it to prefix+fileNumber+suffix
    The +5 lets the fileNumber be a 4 digit number (base 10)
    Why 4 and not 5? That's because the last memory slot if dedicated for the \0 at the end
  */
  char *path = malloc((strlen(prefix)+strlen(prefix)+5)*sizeof(char));
  /*
    While the file path exists, we iterate fileNumber
    We check if a file exists using access, from unistd.h
  */
  do
    sprintf(path, "%s%d%s", prefix, fileNumber++, suffix);
  while(access(path, F_OK) != -1);
  return fileNumber-1;
}

void saveLevel(Bomberman *bbm){
  int fileNumber = 0, i, j, x, y;
  char *prefix = "resources/levels/lvl";
  char *suffix = ".txt";
  FILE *lvl;
  /*
    We alloc the needed memory to path for it to prefix+fileNumber+suffix
    The +5 lets the fileNumber be a 4 digit number (base 10)
    Why 4 and not 5? That's because the last memory slot if dedicated for the \0 at the end
  */
  char *path = malloc((strlen(prefix)+strlen(prefix)+5)*sizeof(char));
  /* o stands for blocks, c for boxes and s for spikes */
  char *objChars = "bcs";
  Objects *objList[3];
  objList[0] = bbm->blocks;
  objList[1] = bbm->boxes;
  objList[2] = bbm->spikes;
  /*
    While the file path exists, we iterate fileNumber
    We check if a file exists using access, from unistd.h
  */
  do
    sprintf(path, "%s%d%s", prefix, fileNumber++, suffix);
  while(access(path, F_OK) != -1);
  lvl = fopen(path, "w");
  /* We can free path */
  free(path);
  if(!lvl)
    exit(EXIT_FAILURE);
  /* We save all blocks, boxes and spikes */
  for(j = 0; j < 3; ++j){
    fprintf(lvl, "%c\n", objChars[j]);
    for(i = 0; i < objList[j]->length; ++i){
      x = objList[j]->list[i]->position->x/bbm->grid->size;
      y = objList[j]->list[i]->position->y/bbm->grid->size;
      if(x > 0 && x < bbm->grid->dimensions->x-1
      && y > bbm->grid->marginTop && y < bbm->grid->marginTop+bbm->grid->dimensions->y-1)
        fprintf(lvl, "%d;%d\n", x, y);
    }
  }
  fclose(lvl);
  debug(0, "Level saved!\n");
}

void loadLevel(Bomberman *bbm, int fileNumber){
  int i, x, y;
  char objChar;
  char *prefix = "resources/levels/lvl";
  char *suffix = ".txt";
  /* Same as in saveLevel */
  char *path = malloc((strlen(prefix)+strlen(prefix)+5)*sizeof(char));
  FILE *lvl;
  Objects *objList[3];
  objList[0] = bbm->blocks;
  objList[1] = bbm->boxes;
  objList[2] = bbm->spikes;
  sprintf(path, "%s%d%s", prefix, fileNumber, suffix);
  lvl = fopen(path, "r");
  if(!lvl)
    exit(EXIT_FAILURE);
  for(i = 0; i < 3; ++i){
    if(fscanf(lvl, "%c", &objChar) == 1){
      if(objChar == "bcs"[i]){
        while(fscanf(lvl, "%d;%d", &x, &y) == 2){
          newObject(objList[i], newCoord(x*bbm->grid->size, y*bbm->grid->size));
        }
      }
    }
  }
  fclose(lvl);
  free(path);
}
