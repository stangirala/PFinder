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

#include "utils.h"

#include "hist_distance.h"
#include "test_feature.h"
#include "getfeatures.h"
#include "sort_match.h"
#include "sort_matches.h"

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


int personfinder (int argc, char **argv, boostfs::path &tempdir, std::vector<std::string> &paths_to_files, std::vector<std::string> &image_type) {

  double score;
  std::shared_ptr<jake::jvVideo> img1, img2, img3, test_image;
  //std::vector<std::string> paths_to_files, image_type, image_index, imfiles, vid_type, vidfiles;
  std::vector<std::string> image_index, imfiles, vid_type, vidfiles;
  std::vector<struct currim_t> imdata;
  std::vector<std::vector<struct currim_t> > viddata;

  boostfs::path pathsfile, imtypes, vidtypes, testim;
  boostfs::ifstream paths, im_types, vid_types, test_im;

  int num_hits, fps, i, j;
  float thresh, scale;

  Log *log = new Log(OFF, "cout");


  std::stringstream strstream;

  // Setup the arguments.
  if (argc < 5 || argc > 9) {
    printf ("Incorrect Usage. Expected \"personfinder paths, im_types, vid_types, test_im[, [num_hits, [thres, [scale, [fp]]]]]\n"
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

    testim = argv[4];
    if (!boost::filesystem::exists(testim)) {
      cout << "test_im argument is incorrect." << endl;
      exit(1);
    }

    num_hits = 10;
    thresh = 3.0;
    scale = 0.5;
    fps = 10;

    if (argc == 6) {
      num_hits = atoi(argv[5]);
    }
    else if (argc == 7) {
      thresh = atoi(argv[6]);
      num_hits = atoi(argv[5]);
    }
    else if (argc == 8) {
      scale = atoi(argv[7]);
      thresh = atoi(argv[6]);
      num_hits = atoi(argv[5]);
    }
    else if (argc == 9) {
      fps = atoi(argv[8]);
      scale = atoi(argv[7]);
      thresh = atoi(argv[6]);
      num_hits = atoi(argv[5]);
    }
  }


  // Get paths to files.
  paths.open(pathsfile);
  if (paths.fail()) {
    cout << "Unable to paths file. Exiting" << endl;
    exit(1);
  }
  while (paths) {
    std::string str;
    getline(paths, str);
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
    if (str != "") {
      paths_to_files.push_back(str);
    }
  }

  // Get image types
  // Change the way extensions are handled here.
  im_types.open(imtypes);
  if (im_types.fail()) {
    cout << "Unable to read im_types file. Exiting" << endl;
    exit(1);
  }
  while (im_types) {
    std::string str;
    getline(im_types, str);
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
    if (str[0] != '.') {
      str.insert(0, ".");
    }
    image_type.push_back(str);
  }

  // Get video types
  vid_types.open(vidtypes, ios::in);
  if (vid_types.fail()) {
    cout << "Unable to read vid_types file. Exiting" << endl;
    exit(1);
  }
  while (vid_types) {
    std::string str;
    getline(vid_types, str);
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
    if (str[0] != '.') {
      str.insert(0, ".");
    }
    vid_type.push_back(str);
  }


  //log->log_msg("File Paths :" << paths_to_files.size() << " File Types: " << image_type.size());

  /* I'm leaving this in here to potray my stupidity at not testing absolute links first. I was caught up on using
   canonical ones. Also, this is another dig at how badly the Boost docs are organized. Maybe its a fault on my person
   but they are quite irritating.*/
  /*std::cout << "TEST: " << boostfs::is_directory(boostfs::path("~/Downloads"));
  for (boostfs::directory_iterator dir(boostfs::path("/home/vtangira/Downloads")), end_itr; dir != end_itr; dir++) {
    std::cout << dir->path() << std::endl;
  }*/


  // Index Image Files
  try {
    for ( i = 0; i < paths_to_files.size(); i++ ) {
      for ( j = 0; j < image_type.size(); j++ ) {
        if (boostfs::is_directory(boostfs::canonical(paths_to_files.at(i)))) {
          for ( boostfs::directory_iterator dir(boostfs::path(paths_to_files.at(i))), end_itr;
                dir != end_itr;
                dir++
              ) {
            if (dir->path().extension().string() == image_type.at(j)) {
              // Check that the image is in jpeg.
              if (dir->path().extension().compare(".jpg") == 0 || dir->path().extension().compare(".jpeg") == 0) {
                cout << "Input Image - " << dir->path().string() << endl;
                imfiles.push_back(dir->path().string());
              }
              else {
                // Convert it and temp it.
                Mat temp = imread(dir->path().string(), CV_LOAD_IMAGE_COLOR);
                vector<int> params;
                params.push_back(CV_IMWRITE_JPEG_QUALITY);
                params.push_back(100);
                string newname = dir->path().parent_path().string() + "/ttemp_" + dir->path().filename().string() + ".jpg";
                cout << "Input Image - " << newname << endl;
                imwrite(newname, temp, params);
                imfiles.push_back(newname);
              }

            }
          }
        }
      }
    }
  } catch (boostfs::filesystem_error e) {
      cout << "Error Code: " << e.code() << endl
           << "Error Msg: " << e.code().message() << endl;
  }

  cout << endl << endl;


  // Looking for people in images.
  Matrix<float, Dynamic, Dynamic> pdata, feat;
  boostfs::path temppath;
  int sizetemp = imfiles.size();
  for (i = 0; i < sizetemp; i++) {

    temppath = imfiles[i];
    getfeatures(temppath, thresh, scale, pdata, feat);
    cout << "PDATA" << pdata << endl;
    cout << "FEAT" << feat << endl;
    cout << endl;

    struct currim_t tempcurrim;
    tempcurrim.feat = feat;
    tempcurrim.det = pdata;
    tempcurrim.path = imfiles[i];
    tempcurrim.type = "im";
    imdata.push_back(tempcurrim);
  }


  // Index all video files.
  try {
    for ( i = 0; i < paths_to_files.size(); i++ ) {
      for ( j = 0; j < vid_type.size(); j++ ) {
        if (boostfs::is_directory(boostfs::canonical(paths_to_files.at(i)))) {
          for ( boostfs::directory_iterator dir(boostfs::path(paths_to_files.at(i))), end_itr;
                dir != end_itr;
                dir++
              ) {
            if (dir->path().extension().string() == vid_type.at(j)) {
              cout << "Input Video - " << dir->path().string() << endl;
              vidfiles.push_back(dir->path().string());
            }
          }
        }
      }
    }
  } catch (boostfs::filesystem_error e) {
      cout << "Error Code: " << e.code() << endl
           << "Error Msg: " << e.code().message() << endl;
  }


  // Split the video into framesCheck that the image is in jpeg.
  //Using temporary directory. boostfs::path tempdir = boostfs::temp_directory_path(); :|
  //boostfs::path tempdir = boostfs::unique_path();
  tempdir = boostfs::unique_path();
  boostfs::create_directory(tempdir);
  cout << "Processing Video" << endl;

  std::vector<std::vector<std::string> > vidframes;
  std::vector<std::string> tempvec;

  vector<int> params;
  params.push_back(CV_IMWRITE_JPEG_QUALITY);
  params.push_back(100);
  std::stringstream heckles;

  // Store each frame by video as a vector of vectors.
  for (i = 0; i < vidfiles.size(); i++) {

    // the part that does the framing.
    jake::jvVideoFrames jf;
    jf.load(vidfiles[i]);

    for (j = 0; j < jf.length() / fps; j++) {

      heckles << tempdir.string() << "/heckles_" << i << "_" << j << ".jpg";

      cv::imwrite(heckles.str(), jf.frame(j), params);

      temppath = heckles.str();
      tempvec.push_back(temppath.string());

      heckles.str(std::string());
      heckles.clear();
    }
    vidframes.push_back(tempvec);
    tempvec.clear();
  }

  for (i = 0; i < vidframes.size(); i++) {
    cout << vidframes[i].size() << endl;
  }

  std::vector<struct currim_t> currimvec;
  for (i = 0; i < vidframes.size(); i++) {
    cout << "VID FRAME SIZE " << vidframes[i].size() << endl;
    for (j = 0; j < vidframes[i].size(); j++) {

      temppath = vidframes[i].at(j);
      cout << "Get features on " << temppath.string() << endl;

      getfeatures(temppath, thresh, scale, pdata, feat);
      cout << "PDATA" << pdata << endl;
      cout << "FEAT" << feat << endl;
      cout << endl;

      struct currim_t tempcurrim;
      tempcurrim.feat = feat;
      tempcurrim.det = pdata;
      tempcurrim.path = vidfiles[i];
      tempcurrim.type = "vid";
      currimvec.push_back(tempcurrim);
      cout << "Saved data" << endl;
    }
    viddata.push_back(currimvec);
  }


  // Relative path does not work.
  Matrix<float, 1, Dynamic> gt_feat;
  test_image.reset(new jake::jvVideoFull());
  test_image->load(testim.string());
  cout << "Loading test image." << endl;

  test_feature(test_image.get(), gt_feat);

  cout << "Extracting testim image features" << endl;

  // Sort matches

  std::vector<struct score_t> matches;
  sort_match(gt_feat, imdata, viddata, matches);

  cout << "Getting top num hits" << endl;

  // Get top numhits from matches.
  std::vector<struct score_t> hits;
  sort_matches(matches, num_hits, hits);


  return 0;
}

// Delete Older ttemp_* files for images before exit and temp frames.
int closing_time(boostfs::path tempdir, std::vector<std::string> paths_to_files, std::vector<std::string> image_type) {

  int i, j;


  cout << endl << "Cleaning up." << endl;

  try {
    // For the frames.
    if (tempdir.string().compare("") != 0) {
      boostfs::remove_all(tempdir);
    }
    // For the converted files.
    for ( i = 0; i < paths_to_files.size(); i++ ) {
      for ( j = 0; j < image_type.size(); j++ ) {
        if (boostfs::is_directory(boostfs::canonical(paths_to_files.at(i)))) {
          for ( boostfs::directory_iterator dir(boostfs::path(paths_to_files.at(i))), end_itr;
              dir != end_itr;
              dir++
              ) {
            if (dir->path().string().find("ttemp_") != string::npos) {
              boostfs::remove(dir->path());
            }

          }
        }
      }
    }
  } catch (boostfs::filesystem_error e) {
      cout << "Error Code: " << e.code() << endl
           << "Error Msg: " << e.code().message() << endl;
    }

  cout << "Exit" << endl;

  return 0;
}

int main(int argc, char **argv) {

  boostfs::path tempdir;
  std::vector<std::string> paths_to_files, image_type;

  personfinder(argc, argv, tempdir, paths_to_files, image_type);

  closing_time(tempdir, paths_to_files, image_type);

  return 0;
}
