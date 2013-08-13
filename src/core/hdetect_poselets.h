/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    hdetect_poselets.cpp
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Header-Only file, hdetect_poselets.cpp
 *
 ********************************************************************
 */

#include <vector>
#include <iostream>

#include <stdio.h>

#include <jakeVideo.h>
#include <Eigen/Dense>

//#include <boost/gil/gill_all.hpp>
#include <boost/filesystem.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/bind.hpp>
#include <boost/timer.hpp>
#include <boost/format.hpp>
#include <boost/ref.hpp>

#include "utils.h"

#include <poselet_api.h>

#pragma once

/** \file hdetect_poselets.cpp
    \brief

    Uses poselets to detect humans in the given image.

 */

using namespace::cv;
using namespace::Eigen;
using namespace::std;
using namespace::poselet_api;
using namespace boost::gil;


template <typename D>
void append_hit(const D &oh, vector<D> &hits) {
  hits.push_back(oh);
}


template <typename D>
void hdetect_poselets(boost::filesystem::path image, float thresh, float scale, MatrixBase<D> &persondata) {

  int i, j;
  string faster_detection, enable_bigq, modelname, modeldir;
  vector<ObjectHit> object_hits, filter;
  vector<PoseletHit> poselet_hits;
  bgr8_image_t img;

  faster_detection = "false";
  enable_bigq = "true";

  ifstream testfile(image.string().c_str());
  if (!testfile) {
    cout << "Cannot open file - " <<  image.string() << endl
         << "Exiting" << endl;
    exit(0);
  }

  // Read image. Uses boost::gil to represent images.
  try {
    jpeg_read_image(image.string().c_str(), img);
  } catch (std::ios_base::failure f) {
    cout << f.what() << endl;
    exit(0);
  }


  // Not using enable_bigq or faster detection yet.


  // Get detected poselets
  modeldir = "/home/vtangira/Downloads/poselets.cpp/data/categories";
  modelname = "person";
  if (InitDetector(modeldir.c_str(), modelname.c_str(), true)) {
    cout << "Failed to load model to detect Humans." << endl;
  }

  cout << "IMAGE SIZE IN hdetect poselets " << img.width() << " " << img.height() << endl;

  Image img_proxy (
    img.width(), img.height(), const_view(img).pixels().row_size(),
    Image::k8Bit, Image::kRGB, interleaved_view_get_raw_data(const_view(img)));

  cout << "IMAGE DATA IN HDETECT POSELETS " << img.width() << " " << img.height() << endl;


  cout << "Running Detector on Input - " << image.string() << endl;

  RunDetector(img_proxy, boost::bind(append_hit<PoseletHit>, _1, boost::ref(poselet_hits)),
                         boost::bind(append_hit<ObjectHit>, _1, boost::ref(object_hits)),
                         true, 0, false);


  // Filter prediction on threshold and return persondata.
  //cout << "DETECTED POSELETS" << endl;
  for (i = 0; i < object_hits.size(); i++) {
      cout << "Found poselet: "
      << object_hits[i].x0 << " "
      << object_hits[i].y0 << " "
      << object_hits[i].width << " "
      << object_hits[i].height << " "
      << object_hits[i].score << endl;
    //cout << "FILTERING CRITERIA SCORE " << object_hits[i].score << endl;
    if (object_hits[i].score > thresh) {
      //cout << "PASSED CRITERIA" << endl;
      // Check image bounds here.
      /*if ( !( object_hits[i].x0 + object_hits[i].width <= img.width() &&
            object_hits[i].y0 + object_hits[i].height <= img.height() )
         ) {
        //cout << "PASSED IMAGE BOUNDS" << endl;
        object_hits[i].width = img.width() - object_hits[i].x0 - 1;
        object_hits[i].height = img.height() - object_hits[i].y0 - 1;
      }
      filter.push_back(object_hits[i]);*/
      if ( ( object_hits[i].x0 + object_hits[i].width <= img.width() &&
            object_hits[i].y0 + object_hits[i].height <= img.height() )
         ) {
        filter.push_back(object_hits[i]);
      }
    }
  }
  //cout << "DONE PRINT" << endl;

  cout << "Filtering Detections." << endl;

  cout << "DETECTIONS ARE - " << endl;
  for (vector<ObjectHit>::iterator itr = filter.begin(); itr != filter.end(); itr++)
    cout << "SCORE " << itr->score << endl;

  if (filter.size() > 0) {

    persondata.derived().resize(1, filter.size() * 4);
    int index = 0;
    for (j = 0; j < filter.size(); j++) {
      persondata(0, index + 0) = filter[j].x0 / scale;
      persondata(0, index + 1) = filter[j].y0 / scale;
      persondata(0, index + 2) = filter[j].width / scale;
      persondata(0, index + 3) = filter[j].height / scale;
      index += 4;
    }
  }


  cout << "Persondata from hdetect_poselets" << persondata << endl;

  cout << "Exiting hdetect_poselets" << endl;


  return;
}
