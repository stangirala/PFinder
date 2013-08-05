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
#include <ostream>
#include <iostream>

#include <drwnBase.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/lexical_cast.hpp>

#include "../src/core/personfinder.h"

// Input order
// Not using absolute paths should work. Should it not consider using them.
// paths_file, im_type, vid_types, test_im, num_hits, thres, scale, fps
// paths_file - Name of .txt file which has paths to the input video/image data. These
//              are the videos and images of interest. Paths can be relative or absolute.
// im_types - Name of .txt file which has types of images (Ex: png,jpg) which are in the paths considered.
// vid_types - Name of .txt file which has types of videos which are in the paths considered.
// test_im - Complete path to read a test image which is cropped picture of object
// num_hits (Default : 10) - Number of top hits to be returned
// thresh (Default : 3.0)- Threshold for person detector - Increase if the detector is finding
//                         a lot of false positives and decrease if detector is missing a object
// scale (Default : 0.5) - To reduce computation time of detector fps (Default : 10). Samples every ten frames.
//
// Example call
// ./_bin/personfinder /home/vtangira/Desktop/person_finder_v20130513/paths1.txt /home/vtangira/Desktop/person_finder_v20130513/imtypes.txt /home/vtangira/Desktop/person_finder_v20130513/vidtypes.txt /home/vtangira/Desktop/person_finder_v20130513/person1.png


namespace boostfs = boost::filesystem;


int main(int argc, char **argv) {

  boostfs::path tempdir;
  std::vector<std::string> paths_to_files, image_type;
  int code;
  std::vector<struct score_t> matches;

  if ((code = personfinder(argc, argv, tempdir, paths_to_files, image_type, matches)) != 0)
    cout << "Error Code - " << code;

  if ((code = closing_time(tempdir, paths_to_files, image_type)) != 0)
    cout << "Error Code - " << code;

  return 0;
}
