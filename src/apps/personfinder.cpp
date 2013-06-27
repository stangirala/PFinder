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

#include "hist_distance.h"
#include "test_feature.h"
//#include "utils.h"

// Input order
// Please use absolute file paths _everywhere_.
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

  std::vector<std::string> paths_to_files, image_type, image_index;

  namespace boostfs = boost::filesystem;

  boostfs::path pathsfile, imtypes, vidtypes, testim;
  boostfs::ifstream paths, im_types, vid_types, test_im;

  int num_hist, fps, i, j;
  float thresh, scale;

  // Log *log = new Log(OFF, "cout");


  std::stringstream strstream;

  // Setup the arguments.
  if (argc < 5 || argc > 9) {
    printf ("Incorrect Usage. Expected \"personfinder paths, im_types, vid_types, test_im[, [num_hist, [thres, [scale, [fp]]]]]\n"
             "Please check the README\n");
  }
  else {
    pathsfile = argv[1];
    if( (!boostfs::exists(pathsfile)) && (!boostfs::is_regular_file(pathsfile)) ) {
      cout << "paths_file argument is incorrect." << endl;
      exit(1);
    }

    imtypes = argv[2];
    if ( (!boost::filesystem::exists(imtypes)) && (!boost::filesystem::is_regular_file(imtypes)) ) {
      cout << "im_type argument is incorrect." << endl;
      exit(1);
    }

    vidtypes = argv[3];
    if ( (!boost::filesystem::exists(vidtypes)) && (!boost::filesystem::is_regular_file(vidtypes)) ) {
      cout << "vid_types argument is incorrect." << endl;
      exit(1);
    }
    vid_types.open(vidtypes);

    testim = argv[4];
    cout << "Actual arg4 '" << argv[4] << "'" << endl;
    cout << "testim file is: " << testim << "\n" << endl << "\n";
    if (!boost::filesystem::exists(testim)) {
      cout << "test_im argument is incorrect." << endl;
      exit(1);
    }

    num_hist = 10;
    thresh = 3.0;
    scale = 0.5;
    fps = 3;

    if (argc == 6) {
      num_hist = atoi(argv[5]);
    }
    else if (argc == 7) {
      thresh = atoi(argv[6]);
      num_hist = atoi(argv[5]);
    }
    else if (argc == 8) {
      scale = atoi(argv[7]);
      thresh = atoi(argv[6]);
      num_hist = atoi(argv[5]);
    }
    else if (argc == 9) {
      fps = atoi(argv[8]);
      scale = atoi(argv[7]);
      thresh = atoi(argv[6]);
      num_hist = atoi(argv[5]);
    }
  }


  // Get paths to files.
  paths.open(pathsfile);
  while (paths) {
    std::string str;
    getline(paths, str);
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
    paths_to_files.push_back(str);
  }


  // Get image types
  im_types.open(imtypes);
  while (im_types) {
    std::string str;
    getline(im_types, str);
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
    image_type.push_back(str);
  }

  //log->msg("File Paths :" << paths_to_files.size() << " File Types: " << image_type.size());

  /* I'm leaving this in here to potray my stupidity at not testing absolute links first. I was caught up on using
   canonical ones. Also, this is another dig at how badly the Boost docs are organized. Maybe its a fault on my person
   but they are quite irritating.*/
  /*std::cout << "TEST: " << boostfs::is_directory(boostfs::path("~/Downloads"));
  std::cout << "TEST: " << boostfs::is_directory(boostfs::path("/home/vtangira/Downloads")) << endl;
  for (boostfs::directory_iterator dir(boostfs::path("/home/vtangira/Downloads")), end_itr; dir != end_itr; dir++) {
    std::cout << dir->path() << std::endl;
  }*/


  try {
    // Index files.
    for (i = 0; i < paths_to_files.size(); i++) {
      for (j = 0; j < image_type.size(); j++) {

        if (  (boostfs::exists(boostfs::status(boostfs::canonical(paths_to_files.at(i))))) &&
              (boostfs::is_directory(boostfs::canonical(paths_to_files.at(i))))
           ) {

          for ( boostfs::directory_iterator dir(boostfs::path(paths_to_files.at(i))), end_itr;
                dir != end_itr;
                dir++
              ) {

            if (dir->extension() == image_type.at(j))
              std::cout << "File: " << dir->path() << std::endl;
          }

          cout << endl;
        }
      }
    }
  } catch (boostfs::filesystem_error e) {
      cout << "Error Code: " << e.code() << endl
           << "Error Msg: " << e.code().message() << endl;
  }

  // Test Code.
  test_image.reset(new jake::jvVideoFull());

  img1.reset(new jake::jvVideoFull());
  img2.reset(new jake::jvVideoFull());
  img3.reset(new jake::jvVideoFull());

  test_image->load(testim.native());


  img1->load("/home/vtangira/test/jake/data/wildturkey.png");
  img2->load("/home/vtangira/test/jake/data/yoyo.avi");
  score = hist_distance(img1.get(), img2.get());
  strstream << "Score:" << score << endl;
  // log->log_msg(strstream.str());
  strstream.str(std::string());

  // Relative path does not work.
  test_feature(test_image.get(), feat);
  strstream << "Size of feature vector is " << feat.size() << endl;
  // log->log_msg(strstream.str());
  strstream.str(std::string());

  strstream << "Feature Vector" << std::endl;
  for (j = 0; j < feat.cols(); j++) {
    if (j % 3 == 0 && j > 0)
      strstream << endl;
    strstream << feat(0, j) << " ";
  }
  // log->log_msg(strstream.str());

  return 0;
}
