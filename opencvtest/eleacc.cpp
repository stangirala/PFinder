#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/core/operations.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

/**  @function main */
int main( int argc, char** argv )
{
  cv::Mat src, dst, hist_b, hist_g, hist_r;
  vector<cv::Mat> v_bgr;
  int binCount;
  float *range;

  if( argc == 1 ) {
    printf("Usage: ./Histogram_Demo <path_to_image>\n");
    return -1;
  }

  /// Load image
  src = cv::imread( argv[1], -1 );

  cv::split(src, v_bgr);

  cout << "Img Size: " << v_bgr[0].size() << endl;;

  cout << "Pixel Norm - " << v_bgr[2].at<int>(20, 19) % 256 << endl;

  return 0;
}

