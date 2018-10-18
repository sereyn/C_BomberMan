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
	int created;
} Editor;

/* Tells if a block is forbidden to the edition or not */
int isForbiddenBlock(int x, int y, int w, int h);

/* Initialises the editor */
Editor *initEditor(Bomberman *bbm);

void createEditor(Editor *editor, Bomberman *bbm);

/* Has to be executed in a game loop: main function of the editor */
void editorLoop(Editor *editor, Bomberman *bbm);

/* Frees the allocated memory */
void freeEditor(Editor *editor);

#endif /* EDITOR */
