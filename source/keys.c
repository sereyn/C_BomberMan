#include "keys.h"

Key *newKey(Keys *keys, MLV_Keyboard_button keyCode){
  /* Some basic initialisation */
  Key *key = malloc(sizeof(Key));
  key->state = 0;
  key->previousState = 0;
  key->keyCode = keyCode;
  keys->list = realloc(keys->list, (++keys->length)*sizeof(Key *));
  keys->list[keys->length-1] = key;
  return key;
}

int isPressed(Key *key){
  return key->state;
}

int isJustPressed(Key *key){
  /* The key has just been pressed if it is currently pressed but weren't on the previous frame */
  return key->state && !key->previousState;
}

Keys *initKeys(){
  /* Some basic initialisation */
  Keys *keys = malloc(sizeof(Keys));
  keys->list = malloc(sizeof(Key *));
  keys->length = 0;
  /* Here we initialise the various keys ever needed */
  keys->s = newKey(keys, MLV_KEYBOARD_s);
  keys->ctrl = newKey(keys, MLV_KEYBOARD_LCTRL);
  keys->escape = newKey(keys, MLV_KEYBOARD_ESCAPE);
  return keys;
}

void updateKeys(Keys *keys){
  /* Has to be called once per frame (so in the main loop) */
  int i = 0;
  Key *key;
  for(; i < keys->length; ++i){
    key = keys->list[i];
    key->previousState = key->state;
    key->state = !MLV_get_keyboard_state(key->keyCode);
  }
}

void freeKeys(Keys *keys){
  /* We free every key and the keys container */
  int i = 0;
  for(; i < keys->length; ++i)
    free(keys->list[i]);
  free(keys->list);
  free(keys);
}
