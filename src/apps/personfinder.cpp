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

  std::shared_ptr<jake::jvVideo> img;

  img.reset(new jake::jvVideoFull());

  img->load("/home/vtangira/test/jake/data/yoyo.avi");

  hist_distance(img.get(), img.get());

  return 0;
}



