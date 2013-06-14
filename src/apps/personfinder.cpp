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

#include <hist_distance.h>
#include <test_feature.h>

int main (int argc, char** argv) {

  double score;
  int i, j;

  Matrix<float, 1, Dynamic> feat;

  std::shared_ptr<jake::jvVideo> img1, img2;

  img1.reset(new jake::jvVideoFull());
  img2.reset(new jake::jvVideoFull());

  img1->load("/home/vtangira/test/jake/data/wildturkey.png");
  img2->load("/home/vtangira/test/jake/data/yoyo.avi");

  score = hist_distance(img1.get(), img2.get());

  printf ("Score: %e\n", score);

  feature_vector(img1.get(), feat);

  printf ("Size of feature vector is %d\n", feat.size());

  for (i = 0; i < feat.rows(); i++) {
    for (j = 0; j < feat.cols(); j++)
      cout << feat << " ";
    cout << endl;
  }


  return 0;
}



