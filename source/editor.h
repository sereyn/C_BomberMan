#ifndef EDITOR
#define EDITOR

#include <MLV/MLV_all.h>
#include "objects.h"
#include "files.h"
#include "bomberman.h"
#include "utils.h"

/* A structure to save editor's current state */
typedef struct{
	/* The tool the user will paint the map with */
	Objects *item;
} Editor;

/* Initialises the editor */
Editor initEditor(Bomberman *bbm);

/* Has to be executed in a game loop: main function of the editor */
void editorLoop(Bomberman *bbm, Editor *editor);

#endif /* EDITOR */
