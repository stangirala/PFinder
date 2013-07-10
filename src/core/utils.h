#include <ostream>
#include <memory>
#include <stdlib.h>
#include <math.h>

#pragma once


enum state_t {
  ON,
  OFF
};


class Log {

  private:
          static state_t DEBUG;
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


class point {

  public:
          float x, y;
          float operator*(class point rhs);
          point operator-(class point rhs);
          point operator+(class point rhs);
          point operator=(class point rhs);

};

struct rectangle {

  point points[4];
}

template <typename Derived>
bool rectint (const Matrix<Derived> a, const Matrix<Derived> b, Matrix<Derived> areamat);
