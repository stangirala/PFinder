#include <stdio.h>

#pragma once


enum state_t {
  ON,
  OFF
};

extern state_t DEBUG;

class Log {

  private:
          static state_t DEBUG;

  public:
          void log_msg(char *msg);
          Log(state_t state) { Log::DEBUG = state; }
          Log() { Log::DEBUG = OFF; }
};
