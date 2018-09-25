#ifndef EDITOR
#define EDITOR

#include "objects.h"
#include "files.h"
#include "bomberman.h"

/* Initialises the editor */
void initEditor(Bomberman *bbm);

/* Has to be executed in a game loop: main function of the editor */
void editorLoop(Bomberman *bbm);

#endif /* EDITOR */
