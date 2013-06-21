#include <ostream>

#pragma once


enum state_t {
  ON,
  OFF
};

extern state_t DEBUG;

class Log {

  private:
          static state_t DEBUG;
          static std::ostream *stream_ptr;

  public:
          void log_msg(char *msg);

          Log(state_t state, char *stream);

          // This version when you need it.
          //Log(state_t state, ios *stream);

          Log(){}

          ~Log() {
            delete stream_ptr;
          }

};
