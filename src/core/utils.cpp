#include <ostream>
#include <iostream>
#include <string>
#include <sstream> // for stringbuf
#include <memory>

#include <Eigen/Dense>
#include <Eigen/Core>

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
void rectint(const MatrixBase<Derived> a, const MatrixBase<Derived> b, MatrixBase<Derived> &areamat) {

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
  return abs((this->x * rhs.x) + (this->y * rhs.y));
}

point& point::operator+(class point rhs) {

  point *temp;

  temp = new point();

  temp->x = this->x + rhs.x;
  temp->y = this->y + rhs.y;

  return *temp;
}

point& point::operator-(class point rhs) {

  point *temp;

  temp = new point();

  temp->x = this->x - rhs.x;
  temp->y = this->y - rhs.y;

  return *temp;
}

point& point::operator/(double rhs) {

  point *temp;

  temp = new point();

  temp->x = this->x / rhs;
  temp->y = this->y / rhs;

  return *temp;
}

bool point::operator==(class point rhs) {

  return ((this->x == rhs.x) && (this->y == rhs.y))?true:false;
}

point& point::operator=(class point rhs) {

  point *temp;

  if (*this == rhs)
    temp = this;
  else {

    temp = new point();

    temp->x = rhs.x;
    temp->y = rhs.y;
  }

  return *temp;
}

void point::print (point p) {

  std::cout << "(" << p.x << ", "
            << p.y << ")" << std::endl;
}


void swap(struct points &a, struct points &b) {

  struct points temp;

  temp.x = a.x; temp.y = a.y;
  a.x = b.x; a.y = b.y;
  b.x = temp.x; b.y = temp.y;
}

void sort_points(class rectangle &rectangle) {

  int i, j, count;

  count = 4;

  // Use your favourite sorting technique here.
  // I am using Bubble Sort.

  for (i = 0; i < (count - 1); i++) {
    for (j = i + 1; j < count; j++) {
      if (rectangle.points[i].x > rectangle.points[j].x)
        swap(rectangle.points[i], rectangle.points[j]);
    }
  }

  for (i = 0; i < (count - 1); i++) {
    for (j = i + 1; j < count; j++) {
      if (points[i].y > points[j].y && points[i].x >= points[i].x)
        swap(points[i], points[j]);
    }
  }

  return 0;
}

// Check if point is inside the space of the rectangle.
bool inRect (struct rectangle rectangle, class point point) {

  class point length, breadth, point_centre;

  sort_points(struct rectange)

  point_centre = point - ((rectangle.points[3] - rectangle.points[1]) / 2);

  point.print(point);
  rectangle.points[1].print(rectangle.points[1]);
  rectangle.points[3].print(rectangle.points[3]);

  std::cout << "Centre is "; point_centre.print(point_centre);

  length = rectangle.points[4] - rectangle.points[3];

  breadth = rectangle.points[4] - rectangle.points[3];

  if (
      ((point_centre - length) * length <= 0) && ((point_centre + length) * length >= 0) &&
      ((point_centre - breadth) * breadth <= 0) && ((point_centre + breadth) * breadth >= 0)
     ) return true;
  else return false;

}

