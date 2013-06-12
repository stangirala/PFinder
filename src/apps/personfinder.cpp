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

int main (int argc, char** argv) {

  double score;

  std::shared_ptr<jake::jvVideo> img1, img2;

  img1.reset(new jake::jvVideoFull());
  img2.reset(new jake::jvVideoFull());

  img1->load("/home/vtangira/test/jake/data/wildturkey.png");
  img2->load("/home/vtangira/test/jake/data/yoyo.avi");

  score = hist_distance(img1.get(), img2.get());

  printf ("Score: %e\n", score);

  return 0;
}



