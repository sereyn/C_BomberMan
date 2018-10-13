#include "utils.h"

void debug(int level, char *format, ...){
  /* Check if the debug message must be print */
  if(level < DEBUG_LEVEL){
    /*
      We use a va_list variable to deal variable arguments length
      We initialise it calling va_start
      vprintf is like printf but it takes a va_list type as the 2nd parameter
      Finally we free the va_list
    */
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
  }
}

int sign(int x){
  return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

Coord *newCoord(int x, int y){
  Coord *coord = malloc(sizeof(Coord));
  coord->x = x;
  coord->y = y;
  return coord;
}
