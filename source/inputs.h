#ifndef INPUTS
#define INPUTS

#include <MLV/MLV_all.h>

/*
  So we made this library for filling the missing functionalities of the MLV keyboard library
  updateKeys needs to be placed in the main loop
  then you can call isPressed which tells if a keyboard button is down or up
  but also isJustPressed if it has been pressed exactly at that frame
*/

typedef struct {
  int state;
  int previousState;
  int inputCode;
  int isKey;
} Input;

typedef struct {
  Input *s, *lctrl, *rctrl, *escape, *lclick, *rclick, *lshift, *rshift,
  *up, *left, *down, *right, *z, *q, *d, *o, *k, *l, *m, *g, *v, *b, *n,
  *enter, *e, *p, *h;
  Input **list;
  int length;
} Inputs;

Input *newInput(Inputs *inputs, int inputCode, int isKey);

int isDown(Input *input);

int isJustDown(Input *input);

Inputs *initInputs();

void updateInputs(Inputs *inputs);

void freeInputs(Inputs *inputs);

#endif /* INPUTS */
