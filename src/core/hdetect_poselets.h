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
  string category, faster_detection, enable_bigq;
  vector<ObjectHit> object_hits, filter;
  vector<PoseletHit> poselet_hits;
  bgr8_image_t img;


  category = "person";
  faster_detection = "false";
  enable_bigq = "true";


  // Read image. Uses boost::gil to represent images.
  jpeg_read_image(image.string(), img);


  // Not using enable_bigq or faster detection yet.


  // Get detected poselets
  InitDetector(image.parent_path().c_str(), image.filename().c_str(), true);

  Image img_proxy (
    img.width(), img.height(), const_view(img).pixels().row_size(),
    Image::k8Bit, Image::kRGB, interleaved_view_get_raw_data(const_view(img)));

  RunDetector(img_proxy, boost::bind(append_hit<PoseletHit>, _1, boost::ref(poselet_hits)),
                         boost::bind(append_hit<ObjectHit>, _1, boost::ref(object_hits)), 
                         true, 0, false);


  // Filter prediction on threshold and return persondata.
  for (i = 0; i < object_hits.size(); i++) {
    if (object_hits[i].score > thresh) {
      filter.push_back(object_hits[i]);
    }
  }

  if (filter.size() > 0) {

    persondata.derived().resize(1, filter.size() * 4);
    for (j = 0; j < filter.size(); j += 4) {
      persondata(0, j + 0) = filter[j].x0 / scale;
      persondata(0, j + 1) = filter[j].y0 / scale;
      persondata(0, j + 2) = filter[j].width / scale;
      persondata(0, j + 3) = filter[j].height / scale;
    }
  }


  return;
}
