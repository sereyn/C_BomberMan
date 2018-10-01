#ifndef EDITOR
#define EDITOR

#include <MLV/MLV_all.h>
#include "objects.h"
#include "files.h"
#include "bomberman.h"
#include "utils.h"

typedef struct {
	int length;
	/* The full list of items available for the player */
	Objects **list;
	/* The current item the user will paint the map with */
	Objects *current;
} Items;

/* Adds a new item into the */
void newItem(Items *items, Objects *item);

typedef struct{
	Items *items;
} Editor;

/* Initialises the editor */
Editor *initEditor(Bomberman *bbm);

/* Has to be executed in a game loop: main function of the editor */
void editorLoop(Editor *editor, Bomberman *bbm);

/* Frees the allocated memory */
void freeEditor(Editor *editor);

#endif /* EDITOR */
