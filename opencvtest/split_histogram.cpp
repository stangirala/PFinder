#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

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

  // One bin for each intensity value. (Called histSize)
  binCount = 256;

  range = (float *) malloc(sizeof(float) * 2);
  range[0] = 0;
  range[1] = 256;

  cv::calcHist(&v_bgr[0], 1, 0, cv::Mat(), hist_b, 1, &binCount, (const float **)&range, true, false );

  cv::calcHist(&v_bgr[1], 1, 0, cv::Mat(), hist_g, 1, &binCount, (const float **)&range, true, false );

  cv::calcHist(&v_bgr[2], 1, 0, cv::Mat(), hist_r, 1, &binCount, (const float **)&range, true, false );

  int hist_w = 512; int hist_h = 512;
  int bin_w = cvRound( (double) hist_w/binCount );

  // Construct an image template.
  cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

  for (int i = 1; i < binCount; i++) {
    cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist_b.at<float>(i-1)) ) ,
                         cv::Point( bin_w*(i), hist_h - cvRound(hist_b.at<float>(i)) ),
                                              cv::Scalar( 255, 0, 0), 2, 8, 0  );

    cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist_g.at<float>(i-1)) ) ,
                         cv::Point( bin_w*(i), hist_h - cvRound(hist_g.at<float>(i)) ),
                                              cv::Scalar( 0, 255, 0), 2, 8, 0  );

    cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist_r.at<float>(i-1)) ) ,
                         cv::Point( bin_w*(i), hist_h - cvRound(hist_r.at<float>(i)) ),
                                              cv::Scalar( 0, 0, 255), 2, 8, 0  );
  }

  cv::normalize(hist_b, hist_b, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

  cv::namedWindow("Test", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Test", histImage );


  /// Wait until user exits the program
  cv::waitKey(0);

  return 0;
}

