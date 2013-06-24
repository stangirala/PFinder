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
#include <boost/filesystem/fstream.hpp>

#include "hist_distance.h"
#include "test_feature.h"
#include "utils.h"

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
// Example call
// ./_bin/personfinder /home/vtangira/Desktop/person_finder_v20130513/paths1.txt /home/vtangira/Desktop/person_finder_v20130513/imtypes.txt /home/vtangira/Desktop/person_finder_v20130513/vidtypes.txt /home/vtangira/Desktop/person_finder_v20130513/person1.png


int main (int argc, char** argv) {

  double score;

  Matrix<float, 1, Dynamic> feat;

  std::shared_ptr<jake::jvVideo> img1, img2, img3, test_image;

  boost::filesystem::fstream paths_file, im_type, vid_types, test_im;

  int num_hist, fps;
  float thresh, scale;

  Log *log = new Log(OFF, "cout");

  boost::filesystem::path pathsfile, imtypes, vidtypes, testim;

  log->log_msg("Person Finder before.");

  if (argc < 5 || argc > 9) {
    printf ("Incorrect Usage. Expected \"personfinder paths_file, im_type, vid_types, test_im[, [num_hist, [thres, [scale, [fp]]]]]\n"
             "Please check the README\n");
  }
  else {
    // Setup the arguments.
    pathsfile = argv[1];
    if( (!boost::filesystem::exists(pathsfile)) && (!boost::filesystem::is_regular_file(pathsfile)) ) {
      cout << "paths_file argument is incorrect." << endl;
      exit(1);
    }
    paths_file.open(pathsfile);

    imtypes = argv[2];
    if ( (!boost::filesystem::exists(imtypes)) && (!boost::filesystem::is_regular_file(imtypes)) ) {
      cout << "im_type argument is incorrect." << endl;
      exit(1);
    }
    im_type.open(imtypes);

    vidtypes = argv[3];
    if ( (!boost::filesystem::exists(vidtypes)) && (!boost::filesystem::is_regular_file(vidtypes)) ) {
      cout << "vid_types argument is incorrect." << endl;
      exit(1);
    }
    vid_types.open(vidtypes);

    testim = argv[4];
    cout << "testim file is: " << testim << endl;
    //if ( (!boost::filesystem::exists(testim)) && (!boost::filesystem::is_regular_file(testim)) ) {
    if (!boost::filesystem::exists(testim)) {
      cout << "test_im argument is incorrect." << endl;
      exit(1);
    }

    num_hist = 10;
    thresh = 3.0;
    scale = 0.5;
    fps = 3;

    if (argc <= 5) {
      num_hist = atoi(argv[4]);
    }
    if (argc <= 6) {
      thresh = atoi(argv[5]);
      num_hist = atoi(argv[4]);
    }
    if (argc <= 7) {
      scale = atoi(argv[6]);
      thresh = atoi(argv[5]);
      num_hist = atoi(argv[4]);
    }
    if (argc <= 8) {
      fps = atoi(argv[7]);
      scale = atoi(argv[6]);
      thresh = atoi(argv[5]);
      num_hist = atoi(argv[4]);
    }
  }


  test_image.reset(new jake::jvVideoFull());

  img1.reset(new jake::jvVideoFull());
  img2.reset(new jake::jvVideoFull());
  img3.reset(new jake::jvVideoFull());

  //test_image->load(testim.native());


  img1->load("/home/vtangira/test/jake/data/wildturkey.png");
  img2->load("/home/vtangira/test/jake/data/yoyo.avi");
  score = hist_distance(img1.get(), img2.get());
  printf ("Score: %e\n", score);

  log->log_msg("Person Finder After.");
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



