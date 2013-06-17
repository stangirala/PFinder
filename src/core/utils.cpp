#include <stdio.h>

#include "utils.h"


void log_msg(char *msg) {

  state_t DEBUG = OFF;

  if (DEBUG == ON) {
    printf ("LOG_MSG: %s\n", msg);
  }
}


