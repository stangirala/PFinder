#include <stdio.h>

#pragma once


enum state_t {
  ON,
  OFF
};

extern state_t DEBUG;

void log_msg(char *msg);
