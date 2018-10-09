#include "inputs.h"

Input *newInput(Inputs *inputs, int inputCode, int isKey){
  /* Some basic initialisation */
  Input *input = malloc(sizeof(Input));
  input->state = 0;
  input->previousState = 0;
  input->inputCode = inputCode;
  input->isKey = isKey;
  inputs->list = realloc(inputs->list, (++inputs->length)*sizeof(Input *));
  inputs->list[inputs->length-1] = input;
  return input;
}

int isDown(Input *input){
  return input->state;
}

int isJustDown(Input *input){
  /* The input has just been down if it is currently down but weren't on the previous frame */
  return input->state && !input->previousState;
}

Inputs *initInputs(){
  /* Some basic initialisation */
  Inputs *inputs = malloc(sizeof(Inputs));
  inputs->list = malloc(sizeof(Input *));
  inputs->length = 0;
  /* Here we initialise the various keys ever needed */
  inputs->s = newInput(inputs, MLV_KEYBOARD_s, 1);
  inputs->lctrl = newInput(inputs, MLV_KEYBOARD_LCTRL, 1);
  inputs->rctrl = newInput(inputs, MLV_KEYBOARD_RCTRL, 1);
  inputs->escape = newInput(inputs, MLV_KEYBOARD_ESCAPE, 1);
  inputs->lclick = newInput(inputs, MLV_BUTTON_LEFT, 0);
  inputs->rclick = newInput(inputs, MLV_BUTTON_RIGHT, 0);
  inputs->lshift = newInput(inputs, MLV_KEYBOARD_LSHIFT, 1);
  inputs->rshift = newInput(inputs, MLV_KEYBOARD_RSHIFT, 1);
  return inputs;
}

void updateInputs(Inputs *inputs){
  /* Has to be called once per frame (so in the main loop) */
  int i = 0;
  Input *input;
  for(; i < inputs->length; ++i){
    input = inputs->list[i];
    input->previousState = input->state;
    /* If isKey, the input is a keyboard key, otherwise it's a mouse button */
    if(input->isKey)
      input->state = !MLV_get_keyboard_state(input->inputCode);
    else
      input->state = !MLV_get_mouse_button_state(input->inputCode);
  }
}

void freeInputs(Inputs *inputs){
  /* We free every key and the keys container */
  int i = 0;
  for(; i < inputs->length; ++i)
    free(inputs->list[i]);
  free(inputs->list);
  free(inputs);
}
