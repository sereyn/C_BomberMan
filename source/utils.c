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