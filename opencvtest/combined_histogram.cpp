#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

/**  @function main */
int main( int argc, char** argv )
{
  cv::Mat src, dst, hist_c;
  int binCount, dims;
  float ranges[3][2];
  int channels;

  if( argc == 1 ) {
    printf("Usage: ./Histogram_Demo <path_to_image>\n");
    return -1;
  }

  /// Load image
  src = cv::imread( argv[1], -1 );

  // One bin for each intensity value. (Called histSize)
  binCount = 256;
  dims = 2;

  for (int i = 0; i < dims; i++) {

    ranges[i][0] = 0;
    ranges[i][1] = 256;
  }

  channels = 3;

  try {
    cv::calcHist((const cv::Mat*)&src, 1, (const int *)&channels, cv::Mat(), hist_c, dims, &binCount, (const float **)&ranges, true, false );
  } catch (cv::Exception &e) {

      printf("ERR_MSG: %s", e.what());
  }

  //cout << hist_c << endl;


  int hist_w = 512; int hist_h = 512;
  int bin_w = cvRound( (double) hist_w/binCount );

  // Construct an image template.
  /*cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

  for (int i = 1; i < binCount; i++) {
    for (int j = 1; j < binCount; j++) {
    cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist_c.at<float>(i-1, j-1)) ) ,
                         cv::Point( bin_w*(i), hist_h - cvRound(hist_c.at<float>(i, j)) ),
                                              cv::Scalar( 255, 0, 0), 2, 8, 0  );
    }

  }

  cv::normalize(hist_c, hist_c, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

  cv::namedWindow("Test", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Test", histImage );


  /// Wait until user exits the program
  cv::waitKey(0);*/

  return 0;
}

