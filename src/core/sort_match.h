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
 *   Header-Only file, sort_match.h
 *
 ********************************************************************
 */

#include <vector>
#include <iostream>

#include <stdio.h>

#include <jakeVideo.h>
#include <Eigen/Dense>

#include <boost/filesystem.hpp>

#include "utils.h"


#pragma once

/** \file sort_match.h
    \brief

    Sorts possible matches between the poselets and the input image.

 */

using namespace::cv;
using namespace::Eigen;
using namespace::std;


template <typename D>
void sort_match(const MatrixBase<D> &gt_feat,
                const std::vector<struct currim_t> &imdata,
                const std::vector<std::vector<currim_t> > &vid_entire_data,
                std::vector<struct score_t> &scores) {

  int i, j, k;
  struct score_t temp;


  // For every set of bounding box detections calculate a difference score, here histogram,
  // between the test image features and the features of the bounding box patch.
  for (i = 0; i < imdata.size(); i++) {
    for (j = 0; j < imdata[i].det.cols() / 4; j++) {

      Matrix<float, Dynamic, Dynamic> h;

      h = imdata[i].feat.row(j);

      cout << "SORT MATCH Sizes being sent in " << gt_feat.rows() << " " << gt_feat.cols() << endl;
      cout << "SORT MATCH Sizes being sent in " << h.rows() << " " << h.cols() << endl;
      temp.match = hist_distance_vec(gt_feat, imdata[i].feat.row(j));
      cout << "Returned" << endl;

      cout << "imdata det size " << imdata[i].det.rows() << " " << imdata[i].det.cols() << endl;

      temp.box(0, 0) = imdata[i].det(0, j*4);
      temp.box(0, 1) = imdata[i].det(0, j*4 + 1);
      temp.box(0, 2) = imdata[i].det(0, j*4 + 2);
      temp.box(0, 3) = imdata[i].det(0, j*4 + 3);

      temp.path = imdata[i].path;
      temp.frame = 1;
      temp.type = "im";

      scores.push_back(temp);
    }
  }

  cout << "done sorting image files " << endl;

  for (i = 0; i < vid_entire_data.size(); i++) {
    for (j = 0; j < vid_entire_data[i].size(); j++) {
      for (k = 0; k < vid_entire_data[i].at(j).det.cols() / 4; k++) {

        temp.match = hist_distance_vec(gt_feat, vid_entire_data[i].at(j).feat.row(k));

        temp.box(0, 0) = vid_entire_data[i].at(j).det(0, k*4);
        temp.box(0, 1) = vid_entire_data[i].at(j).det(0, k*4 + 1);
        temp.box(0, 2) = vid_entire_data[i].at(j).det(0, k*4 + 2);
        temp.box(0, 3) = vid_entire_data[i].at(j).det(0, k*4 + 3);

        temp.path = vid_entire_data[i].at(j).path;
        temp.frame = j;
        temp.type = "vid";

        scores.push_back(temp);
      }
    }
  }

  cout << "done sorting video files" << endl;




}
