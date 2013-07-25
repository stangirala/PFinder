#include <ostream>
#include <iostream>
#include <string>
#include <sstream> // for stringbuf
#include <memory>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/Core>
#include <cv.h>
#include <cxcore.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
          inline void log_msg(std::string msg);

          inline Log(state_t state, std::string stream);

          // This version when you need it.
          //Log(state_t state, ios *stream);

          Log(){}

          ~Log() {
          }

};

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
      stream_ptr.reset(new std::iostream(buffer));
    }
  }

}

////////////////////////////////////////////////////////////////////////////////////

class point {

  public:
          float x, y;

          inline float operator*(class point rhs);
          inline point& operator*(int num);
          inline point& operator-(class point rhs);
          inline point& operator+(class point rhs);
          inline void operator=(class point rhs);
          inline point& operator/(double rhs);
          inline bool operator==(class point rhs);
          inline bool operator!=(class point rhs);

          inline static void print (point p);

};

class rectangle {

  public:
    point points[4];

    //inline void sort_points();

    inline static void swap(point &a, point &b);

    inline static void sort_points(class rectangle &rectangle);

    inline static bool inRect (rectangle rectangle, point point);
};


template <typename D1, typename D2, typename D3>
void alignedRectInt(const MatrixBase<D1> &a, const MatrixBase<D2> &b, MatrixBase<D3> &areamat);

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
  return (this->x * rhs.x) + (this->y * rhs.y);
}

point& point::operator*(int num) {

  this->x *= num;
  this->y *= num;

  return *this;
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

void point::operator=(class point rhs) {

  if (this != &rhs) {

    this->x = rhs.x;
    this->y = rhs.y;
  }
}

bool point::operator!=(class point rhs) {

  bool result;

  if ((this->x == rhs.x) || (this->y == rhs.y))
    result = true;
  else  result = false;

  return result;
}

void point::print (point p) {

  std::cout << "(" << p.x << ", "
            << p.y << ")" << std::endl;
}


void rectangle::swap(point &a, point &b) {

  point temp;

  temp.x = a.x; temp.y = a.y;
  a.x = b.x; a.y = b.y;
  b.x = temp.x; b.y = temp.y;
}

void rectangle::sort_points(class rectangle &rectangle) {

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
      if (
            rectangle.points[i].y > rectangle.points[j].y &&
            rectangle.points[i].x >= rectangle.points[i].x
         )
        swap(rectangle.points[i], rectangle.points[j]);
    }
  }
}

// Check if point is inside the space of the rectangle.
bool rectangle::inRect (rectangle rectangle, point point) {

  class point length, breadth, point_centre;
  bool result;


  rectangle::sort_points(rectangle);

  if (point.x <= 0 && point.y <= 0)
    point_centre = ((rectangle.points[2] - rectangle.points[0])) - point*2;
  else
    point_centre = point*2 - ((rectangle.points[2] - rectangle.points[0]));

  length = rectangle.points[1] - rectangle.points[0];

  breadth = rectangle.points[2] - rectangle.points[1];

  if (
      ((point_centre - length) * length < 0) && ((point_centre + length) * length >= 0) &&
      ((point_centre - breadth) * breadth < 0) && ((point_centre + breadth) * breadth >= 0)
     ) result = true;
  else result = false;

  return result;
}

template <typename D1, typename D2, typename D3>
void alignedRectInt(const MatrixBase<D1> &a, const MatrixBase<D2> &b, MatrixBase<D3> &areamat) {

  int i, j;
  double x11, x21, x12, x22, y11, y21, y12, y22, xinter, yinter;
  rectangle temprect, rect1, rect2;
  std::vector<rectangle> rectangles1, rectangles2;

  for (i = 0; i < a.rows(); i++) {


    temprect.points[0].x = a(i,0); temprect.points[0].y = a(i, 1);
    temprect.points[1].x = a(i,0) + a(i, 2); temprect.points[1].y = a(i, 1);
    temprect.points[2].x = a(i,0) + a(i, 2); temprect.points[2].y = a(i, 1) + a(i, 3);
    temprect.points[3].x = a(i,0); temprect.points[3].y = a(i, 1) + a(i, 3);

    std::cout << "rect 1" << std::endl;
    point::print(temprect.points[0]);
    point::print(temprect.points[1]);
    point::print(temprect.points[2]);
    point::print(temprect.points[3]);

    // In case distances are negative.
    rectangle::sort_points(temprect);

    rectangles1.push_back(temprect);
  }

  for (i = 0; i < b.rows(); i++) {

    temprect.points[0].x = b(i,0); temprect.points[0].y = b(i, 1);
    temprect.points[1].x = b(i,0) + b(i, 2); temprect.points[1].y = b(i, 1);
    temprect.points[2].x = b(i,0) + b(i, 2); temprect.points[2].y = b(i, 1) + b(i, 3);
    temprect.points[3].x = b(i,0); temprect.points[3].y = b(i, 1) + b(i, 3);

    std::cout << "rect 2" << std::endl;
    point::print(temprect.points[0]);
    point::print(temprect.points[1]);
    point::print(temprect.points[2]);
    point::print(temprect.points[3]);

    // In case distances are negative.
    rectangle::sort_points(temprect);

    rectangles2.push_back(temprect);
  }

  areamat.derived().resize(rectangles1.size(), rectangles2.size());

  for (i = 0; i < rectangles1.size(); i++) {
    for (j = 0; j < rectangles2.size(); j++) {

      rect1 = rectangles1[i]; rect2 = rectangles2[j];

      x11 = rect1.points[0].x; y11 = rect1.points[0].y;
      x12 = rect1.points[2].x; y12 = rect1.points[2].y;

      x21 = rect2.points[0].x; y21 = rect2.points[0].y;
      x22 = rect2.points[2].x; y22 = rect2.points[2].y;

      xinter = fmax(0, (fmin(x12, x22) - fmax(x11, x21)));
      yinter = fmax(0, (fmin(y12, y22) - fmax(y11, y21)));

      areamat(i, j) = (xinter * yinter);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////

// Matrix Operations

template <typename D1, typename D2>
void repmat(const MatrixBase<D1> &inp, int r1, int c1, MatrixBase<D2> &out) {

  int i, j, oldr, oldc, newr, newc;


  oldr = inp.rows();  oldc = inp.cols();
  newr = inp.rows() * r1;  newc = inp.cols() * c1;

  //out.derived().resize(newr, newc);
  out.resize(newr, newc);

  for (i = 0; i < newr; i++) {
    for (j = 0; j < newc; j++) {
      out(i, j) = inp(i % oldr, j % oldc);
    }
  }

  return;
}

template <typename D1, typename D2>
void reshape(const MatrixBase<D1> &inp, int r, int c, MatrixBase<D2> &out) {

  int i, j, k, l;


  k = 0; l = 0;
  for (i = 0; i < r; i++) {
    for (j = 0; j < c; j++) {
      out(j, i) = inp(l, k);

      if (l == inp.rows()) {l = 0; k++;} else l++;
    }
  }

  return;
}

////////////////////////////////////////////////////////////////////////////////////

// Wrapper class for cv::Mat access.

class cvMatAt {

  private:
    std::vector<cv::Mat> channels;

  public:
    cvMatAt(cv::Mat image) {
      cv::split(image, channels);
    }

    cvMatAt(std::string image) {
      cv::Mat img;
      img = cv::imread(image, CV_LOAD_IMAGE_COLOR);
      cv::split(img, channels);
    }

    // Three channel image for now. No checking. Use va_list later.
    template <typename D>
    int At(int i, int j, int k);

};


// i, j are on the plane. k is the colour channel.
// width*height*channel --> i*j*k
// opencv stores it as height*width*channel. Indices are inverted here to match matlab.
template <typename D>
int cvMatAt::At(int i, int j, int k) {

  if (k > 2) {
    std::cout << "Exceeds matrix dimension k for cvMatAt" << std::endl;
    exit(0);
  }

  if (i > channels[k].size().width) {
    std::cout << "Exceeds matrix dimension i for cvMatAt" << std::endl;
    exit(0);
  }

  if (j > channels[k].size().height) {
    std::cout << "Exceeds matrix dimension j for cvMatAt" << std::endl;
    exit(0);
  }

  return (channels[k].at<D>(j, i) % 256);

}
