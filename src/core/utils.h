#include <ostream>
#include <memory>
#include <stdlib.h>
#include <math.h>

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
          void log_msg(std::string msg);

          Log(state_t state, std::string stream);

          // This version when you need it.
          //Log(state_t state, ios *stream);

          Log(){}

          ~Log() {
          }

};

////////////////////////////////////////////////////////////////////////////////////

class point {

  public:
          float x, y;

          float operator*(class point rhs);
          point& operator*(int num);
          point& operator-(class point rhs);
          point& operator+(class point rhs);
          void operator=(class point rhs);
          point& operator/(double rhs);
          bool operator==(class point rhs);
          bool operator!=(class point rhs);

          static void print (point p);

};

class rectangle {

  public:
    point points[4];

    void sort_points();
};

void sort_points(class rectangle &rectangle);

bool inRect(struct rectangle rectangle, class point point);

template <typename D1, typename D2, typename D3>
void alignedRectInt(const MatrixBase<D1> &a, const MatrixBase<D2> &b, MatrixBase<D3> &areamat);

///////////////////////////////////////////////////////////////////////////////////

// Matrix Operations

template<typename D1, typename D2>
void repmat(const MatrixBase<D1> &inp, int r1, int c1, MatrixBase<D2> &out);

template<typename D1, typename D2>
void reshape(const MatrixBase<D1> &inp, int r, int c, MatrixBase<D2> &out);

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
    int At(int i, int j, int k);
};
