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
  inputs->up = newInput(inputs, MLV_KEYBOARD_UP, 1);
  inputs->left = newInput(inputs, MLV_KEYBOARD_LEFT, 1);
  inputs->down = newInput(inputs, MLV_KEYBOARD_DOWN, 1);
  inputs->right = newInput(inputs, MLV_KEYBOARD_RIGHT, 1);
  inputs->z = newInput(inputs, MLV_KEYBOARD_z, 1);
  inputs->q = newInput(inputs, MLV_KEYBOARD_q, 1);
  inputs->d = newInput(inputs, MLV_KEYBOARD_d, 1);
  inputs->o = newInput(inputs, MLV_KEYBOARD_o, 1);
  inputs->k = newInput(inputs, MLV_KEYBOARD_k, 1);
  inputs->l = newInput(inputs, MLV_KEYBOARD_l, 1);
  inputs->m = newInput(inputs, MLV_KEYBOARD_m, 1);
  inputs->g = newInput(inputs, MLV_KEYBOARD_g, 1);
  inputs->v = newInput(inputs, MLV_KEYBOARD_v, 1);
  inputs->b = newInput(inputs, MLV_KEYBOARD_b, 1);
  inputs->n = newInput(inputs, MLV_KEYBOARD_n, 1);
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
