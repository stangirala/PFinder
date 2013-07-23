/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    getfeature.cpp
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Source file, feature_vector.cpp
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
#include "feature_vector.h"

/** \file getfeature.cpp
    \brief

    \arg1 pdata is a martix from which features are extracted.
    \arg2 img is a an input image.
    \arg3 return value containing the feature vector.

    Extracts features from pdata using img and retuns feat containing features.
    It does so by obtaining a histogram.

 */


using namespace::Eigen;
using namespace::cv;
using namespace::std;

template <typename D1, typename D2>
void feature_vector(const MatrixBase<D1> &pdata, const Mat &img, MatrixBase<D2> &feat) {

  int n, i, j, l, m, n;
  float sum;
  Matrix<float, Dynamic, Dynamic> curr;
  class cvMatAt image(img);
  jake::jvColorHistogramProjection projector;
  shared_ptr<jake::jvVideoFull> image;
  vector<jvVideoFeature> imhist;
  jake::jvMat3D temp;
  Mat inputframe;



  n = 30;

  projector(n/3, n/3, n/3, n/3, n/3, 1);

  feat.derived() = Matrix<float, Dynamic, Dynamic>::Zero(pdata.cols() / 4, n);

  curr.resize(0, pdata.cols());
  for (i = 0; i < pdata.cols() / 4; i++) {
    for (j = i*4; j < (i+1) * 4; j++) {
      curr(0, j) = pdata(0, j);
    }

    curr(0, 0) = ceil(curr(0, 0));
    curr(0, 1) = ceil(curr(0, 1));
    curr(0, 2) = floor(curr(0, 2));
    curr(0, 3) = floor(curr(0, 3));

    // Setup a jvMat3D object. Fill it up and then setup a jvVideoFull object.
    // length, height, width
    temp.getvolume<int>(img, inputframe, 1, 1,
                        curr(0, 0), curr(0, 0) + curr(0, 2), curr(0, 1), curr(0, 1) + curr(0, 3));

    image.reset(new jake::jvVideoFull(inputframe))

    projector.project(*(image.get()), imhist);

    // Normalize and collect histogram for each channel.
    sum = 0;
    for (l = 0; l < n/3; l++) {
      sum += imhist[0][l];
    }
    for (l = 0; l < n/3; l++) {
      feat(i, l) = imhist[0][l] / sum;
    }

    sum = 0;
    for (l = 0; l < n/3; l++) {
      sum += imhist[1][l];
    }
    for (l = 0; l < n/3; l++) {
      feat(i + n/3, l + n/3) = imhist[1][l] / sum;
    }

    sum = 0;
    for (l = 0; l < n/3; l++) {
      sum += imhist[2][l];
    }
    for (l = 0; l < n/3; l++) {
      feat(i + 2*n/3, l + 2*n/3) = imhist[2][l] / sum;
    }
  }

  return;
}
