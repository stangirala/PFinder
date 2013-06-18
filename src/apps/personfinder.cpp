/*******************************************************************
 * Test App
 * You can haz GPL license.
 *
 *******************************************************************
 */

#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory>

#include <drwnBase.h>

#include <boost/filesystem.hpp>

#include "hist_distance.h"
#include "test_feature.h"
#include "utils.h"


int main (int argc, char** argv) {

  double score;

  Matrix<float, 1, Dynamic> feat;

  std::shared_ptr<jake::jvVideo> img1, img2, img3, test_image;

  boost::filesystem3::path pathsfile, imtype, vidtypes, testim;
  boost::filesystem3::ifstream paths_file, im_type, vid_types, test_im;

  int num_hist, fps;
  float thresh, scale;


  // Input order
  // paths_file, im_type, vid_types, test_im, num_hist, thres, scale, fps
  // paths_file - Name of .txt file which has paths to the input video/image data. These
  //              are the videos and images of interest. Paths can be relative or absolute.
  // im_types - Name of .txt file which has types of images (Ex: png,jpg) which are in the paths considered.
  // vid_types - Name of .txt file which has types of videos which are in the paths considered.
  // test_im - Complete path to read a test image which is cropped picture of object
  // num_hits (Default : 10) - Number of top hits to be returned
  // thresh (Default : 3.0)- Threshold for person detector - Increase if the detector is finding
  //                         a lot of false positives and decrease if detector is missing a object
  // scale (Default : 0.5) - To reduce computation time of detector fps (Default : 3) - Frames per second (fps) 
  //                         at which videos would be processed.

  // Index Image Files

  if (argc < 4 || argc > 8) {
    printf ("Incorrect Usage. Expected \"personfinder paths_file, im_type, vid_types, test_im[, [num_hist, [thres, [scale, [fp]]]]]\n"
             "Please check the README");
  }
  else {
    // Setup the arguments.
    pathsfile.path(argv[0]);
    if( (!exists(paths_file)) && (!is_regular_file(pathsfile)) ) {
      cout << "paths_file argument is incorrect." << endl;
    }
    paths_file.fin(pathsfile);

    imtypes.path(argv[1]);
    if ( (!exists(imtypes)) && (!is_regular_file(imtypes)) ) {
      cout << "im_type argument is incorrect." << endl;
    }
    im_type.fin(imtypes);

    vidtypes.path(argv[2]);
    if ( (!exists(vidtypes)) && (!is_regular_file(vidtypes)) ) {
      cout << "vid_types argument is incorrect." << endl;
    }
    vid_types.fin(vidtypes);

    testim.path(argv[3]);
    if ( (!exists(testim)) && (!is_regular_file(testim)) ) {
      cout << "test_im argument is incorrect." << endl;
    }

    num_hist = 10;
    thresh = 3.0;
    scale = 0.5;
    fps = 3;

    if (argc <= 5) {
      num_hist = argv[4];
    }
    if (argc <= 6) {
      thres = argv[5];
      num_hist = argv[4];
    }
    if (argc <= 7) {
      scale = argv[6];
      thresh = argv[5];
      num_hist = argv[4];
    }
    if (argc <= 8) {
      fps = argv[7];
      scale = argv[6];
      thresh = argv[5];
      num_hist = argv[4];
    }
  }


  test_image.reset(new jake::jvVideoFull());

  img1.reset(new jake::jvVideoFull());
  img2.reset(new jake::jvVideoFull());
  img3.reset(new jake::jvVideoFull());

  test_image->load(testim);


  img1->load("/home/vtangira/test/jake/data/wildturkey.png");
  img2->load("/home/vtangira/test/jake/data/yoyo.avi");
  score = hist_distance(img1.get(), img2.get());
  printf ("Score: %e\n", score);

  // Relative path does not work.
  test_feature(test_image.get(), feat);

  //printf ("\n\nSize of feature vector is %ld\n\n", feat.size());

  /*for (j = 0; j < feat.cols(); j++) {
    if (j % 3 == 0 && j > 0)
      cout << endl;
    cout << feat(0, j) << " ";
  }
  cout << endl;*/

  return 0;
}



