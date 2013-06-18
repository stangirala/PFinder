#include <stdio.h>

#include "utils.h"


//extern state_t DEBUG;

void Log::log_msg(char *msg) {

  //state_t DEBUG;

  if (DEBUG == ON) {
    printf ("LOG_MSG: %s\n", msg);
  }
}

