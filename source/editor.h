#ifndef EDITOR
#define EDITOR

#include <MLV/MLV_all.h>
#include "objects.h"
#include "files.h"
#include "utils.h"
#include "grid.h"

/* A structure to save editor's current state */
typedef struct{
	/* The tool the user will paint the map with */
	Objects *item;
	Objects **items;
	int length;
} Editor;

/* Initialises the editor */
Editor *initEditor(Grid *grid);

/* Destroy the editor */
void destroyEditor(Editor *editor);

/* Has to be executed in a game loop: main function of the editor */
void editorLoop(Bomberman *bbm, Editor *editor);

/* A copy of newObjects but with toolbar compat. */
void newItem(Editor *editor, Objects *objects, int x, int y);

#endif /* EDITOR */
