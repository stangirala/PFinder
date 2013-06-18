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

#include "hist_distance.h"
#include "test_feature.h"
#include "utils.h"


int main (int argc, char** argv) {

  double score;

  Matrix<float, 1, Dynamic> feat;

  std::shared_ptr<jake::jvVideo> img1, img2, img3;

  img1.reset(new jake::jvVideoFull());
  img2.reset(new jake::jvVideoFull());
  img3.reset(new jake::jvVideoFull());


  img1->load("/home/vtangira/test/jake/data/wildturkey.png");
  img2->load("/home/vtangira/test/jake/data/yoyo.avi");
  score = hist_distance(img1.get(), img2.get());
  printf ("Score: %e\n", score);

  // Relative path does not work.
  //img3->load("~/Desktop/person_finder_v20130513/person1.png");
  img3->load("/home/vtangira/Desktop/person_finder_v20130513/person1.png");
  feature_vector(img3.get(), feat);

  //printf ("\n\nSize of feature vector is %ld\n\n", feat.size());

  /*for (j = 0; j < feat.cols(); j++) {
    if (j % 3 == 0 && j > 0)
      cout << endl;
    cout << feat(0, j) << " ";
  }
  cout << endl;*/


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

  if (argc < 5) {
    printf ("The first five inputs are mandatory. You have missed them.\n");
  }
  else if (argc > 8){
    printf ("There are too many input arguments. Eight is the maximum.\n");
  }
  else {
  // Setup the arguments.
  }


  return 0;
}



