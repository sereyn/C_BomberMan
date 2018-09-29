#ifndef UTILS
#define UTILS

/*
  We use this file to define some convenient structures or functions
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define DEBUG_LEVEL 3

/*
  debug is basically a copy of printf
  except when you call the function, you have to choose a level of debugging
  if DEBUG_LEVEL isn't higher than that level, the debug message won't show up
  In a release version, DEBUG_LEVEL is meant to be 0
*/
void debug(int level, char *format, ...);

/* A coordinate structure for variables in RxR */
typedef struct {
  int x;
  int y;
} Coord;

#endif /* UTILS */
