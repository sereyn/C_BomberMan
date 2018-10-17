#ifndef UTILS
#define UTILS

/*
  We use this file to define some convenient structures or functions
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define DEBUG_LEVEL 5

/*
  debug is basically a copy of printf
  except when you call the function, you have to choose a level of debugging
  if DEBUG_LEVEL isn't higher than that level, the debug message won't show up
  In a release version, DEBUG_LEVEL is meant to be 0
*/
void debug(int level, char *format, ...);

/* sign returns 1 if x is positive, -1 if x is negative and 0 otherwise */
int sign(int x);

/* A coordinate structure for variables in RxR */
typedef struct {
  int x;
  int y;
} Coord;

/* You have to manually free a coord created with newCoord */
Coord *newCoord(int x, int y);

#endif /* UTILS */
