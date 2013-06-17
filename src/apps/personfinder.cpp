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

  return 0;
}



