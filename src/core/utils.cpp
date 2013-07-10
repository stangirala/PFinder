#include <ostream>
#include <iostream>
#include <string>
#include <sstream> // for stringbuf
#include <memory>

#include "utils.h"

state_t Log::DEBUG = OFF;
//std::ostream *Log::stream_ptr = nullptr;
std::shared_ptr<std::ostream> Log::stream_ptr;

void Log::log_msg(std::string msg) {

  if (DEBUG == ON) {
    *(stream_ptr.get()) << "LOG_MSG: " << msg << std::endl;
  }
}

Log::Log(state_t state, std::string stream) {

  if (DEBUG != ON) {
    DEBUG = state;
  }

  if (Log::stream_ptr == nullptr) {
    if (stream == "cout") {
      std::streambuf *buffer = std::cout.rdbuf();
      Log::stream_ptr.reset(new std::iostream(buffer));
    }
  }

}


///////////////////////////////////////////////////////////////////////////////


// Calculate the rectangular area intesection between the two
// rectanges represented by the Matrix objects.
template <typename Derived>
void rectint(const Matrix<Derived> a, const Matrix<Derived> b, Matrix<Derived> &areamat) {

  int i, j;
  std::vector<struct points> rect1, rect2;
  struct points temp;

  areamat.derived().resize(a.rows(), b.rows());


  // walk over the two rectangles and do stuff.

  for (i = 0; i < a.rows(); i++) {

    temp.x = a.at(i, 0);
    temp.y = a.at(i, 1);
    rect1.pushback(temp);

    temp.x = a.at(i, 0) + a.at(i, 2);
    temp.y = a.at(i, 1);
    rect1.pushback(temp);

    temp.x = a.at(i, 0) + a.at(i, 2);
    temp.y = a.at(i, 1) + a.at(i, 3);
    rect1.pushback(temp);

    temp.x = a.at(i, 0);
    temp.y = a.at(i, 1) + a.at(i, 3);
    rect1.pushback(temp);
  }

  for (i = 0; i < b.rows(); i++) {

    temp.x = b.at(i, 0);
    temp.y = b.at(i, 1);
    rect2.pushback(temp);

    temp.x = b.at(i, 0) + a.at(i, 2);
    temp.y = b.at(i, 1);
    rect2.pushback(temp);

    temp.x = b.at(i, 0) + a.at(i, 2);
    temp.y = b.at(i, 1) + a.at(i, 3);
    rect2.pushback(temp);

    temp.x = b.at(i, 0);
    temp.y = b.at(i, 1) + a.at(i, 3);
    rect2.pushback(temp);
  }


  // They intersect.
  if (
      (rect1.at(0).x < rect2.at(1).x && rect1.at(1).x > rect2.at(0).x) &&
      (rect1.at(0).y < rect2.at(1).y && rect1.at(1).y > rect2.at(0).y)
     ) {
  }
}

float point::operator*(class point rhs) {
  return abs((this->.x * rhs.x) + (this->y * rhs.y));
}

point& point::operator+(class point rhs) {

  point *temp;

  temp = new point();

  temp->x = this->x + rhs->x;
  temp->y = this->y + rhs->y;

  return *temp;
}

point& point::operator-(class point rhs) {

  point *temp;

  temp = new point();

  temp->x = this->x - rhs->x;
  temp->y = this->y - rhs->y;

  return *temp
}

point& point::operator=(class point rhs) {

  point *temp;

  if (*this == rhs)
    temp = this;
  else {

    temp = new point();

    temp->x = rhs->x;
    temp->y = rhs->y;
  }

  return temp;
}

// Check if point is inside the space of the rectangle.
bool inRect (struct rectangle rectangle, struct point point) {

  float length, breadth;
  class point point_centre;

  point_centre = point - (rectangle.points[1] - rectangle.points[3])

  length = rectangle.points[4] - rectangle.pointsp[3];

  breadth = rectangle.points[4] - rectangle.points[3];

  if (
      ((point_centre - length) * length <= 0) && ((point_centre + length) * length >= 0) &&
      ((point_centre - breadth) * breadth <= 0) && ((point_centre + breadth) * breadth >= 0)
     ) return true;
  else return false;

}

