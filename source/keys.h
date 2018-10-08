#ifndef KEYS
#define KEYS

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
  MLV_Keyboard_button keyCode;
} Key;

typedef struct {
  Key *s, *ctrl, *escape;
  Key **list;
  int length;
} Keys;

Key *newKey(Keys *keys, MLV_Keyboard_button keyCode);

int isPressed(Key *key);

int isJustPressed(Key *key);

Keys *initKeys();

void updateKeys(Keys *keys);

void freeKeys(Keys *keys);

#endif /* KEYS */
