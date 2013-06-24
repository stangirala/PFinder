#include <ostream>
#include <memory>

#pragma once


enum state_t {
  ON,
  OFF
};


class Log {

  private:
          static state_t DEBUG;
          //statuc std::ostream *stream_ptr;
          static std::shared_ptr<std::ostream> stream_ptr;

  public:
          void log_msg(std::string msg);

          Log(state_t state, std::string stream);

          // This version when you need it.
          //Log(state_t state, ios *stream);

          Log(){}

          ~Log() {
          }

};
