#ifndef EDITOR
#define EDITOR

#include <MLV/MLV_all.h>
#include "objects.h"
#include "files.h"
#include "bomberman.h"
#include "utils.h"
#include "inputs.h"

typedef struct {
  int length;
  /* The full list of items available for the player */
  Objects **list;
  /* The current item the user will paint the map with */
  int current;
} Items;

typedef struct{
  Items *items;
} Editor;

/* Initialises the editor */
Editor *initEditor(Bomberman *);

/* Has to be executed in a game loop: main function of the editor */
void editorLoop(Editor *, Bomberman *);

/*
  Frees the allocated memory
  Has to be a pointer of pointer
*/
void freeEditor(Editor **);

#endif /* EDITOR */
