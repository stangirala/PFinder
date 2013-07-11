#include <ostream>
#include <memory>
#include <stdlib.h>
#include <math.h>

#include <Eigen/Dense>
#include <Eigen/Core>

#pragma once

using namespace::Eigen;

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
          point& operator-(class point rhs);
          point& operator+(class point rhs);
          point& operator=(class point rhs);
          point& operator/(double rhs);
          bool operator==(class point rhs);

          void print (point p);

};

struct rectangle {

  point points[4];
};

bool inRect(struct rectangle rectangle, class point point);

template <typename Derived>
bool rectint (const MatrixBase<Derived> a, const MatrixBase<Derived> b, MatrixBase<Derived> areamat);
