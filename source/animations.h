#ifndef ANIMATIONS
#define ANIMATIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <MLV/MLV_all.h>
#include "utils.h"

/* The basic Animation structure */
typedef struct {
  double speed;
  double index;
  MLV_Image **list;
  int length;
} Animation;

/* The Animations structure's purpose is to easily free all of the Animation structures */
typedef struct {
  Animation **list;
  int length;
} Animations;

Animations *initAnimations(void);

/*
  When creating a new animation, you need to provide the string of the file pattern
  (i.e. "bomb%d.png" if your animation is "bomb0.png", "bomb1.png", ..., "bomb5.png")
*/
Animation *newAnimation(Animations *animations, char *filePattern, Coord *dimensions, double speed, double rotation);

/* Draws the animation to the screen at the coordinates (x, y) */
void drawAnimation(Animation *animation, int x, int y);

/* Frees the animation */
void freeAnimation(Animation *animation);

/* Update all the animations */
void updateAnimations(Animations *animations);

/* Frees all the animations */
void freeAnimations(Animations *animations);

#endif /* ANIMATIONS */
