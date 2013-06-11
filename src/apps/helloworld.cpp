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

  jake::jvVideoFrames *img;

  img = new jake::jvVideoFrames();

  img->load("~/test/jake/data/yoyo.avi");

  hist_distance(img, img);

  return 0;
}



