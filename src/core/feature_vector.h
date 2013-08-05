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
 *   Header-Only file, feature_vector.cpp
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

  int n, i, j, l;
  float sum;
  Matrix<float, Dynamic, Dynamic> curr;
  jake::jvColorHistogramProjection *projector;
  shared_ptr<jake::jvVideoFull> image;
  vector<shared_ptr<jake::jvVideoFeature> > imhist;
  jake::jvColorHistogramFeature *hist;
  jake::jvMat3D temp;
  Mat inputframe;

  cout << "Entering feature vector" << endl;

  n = 30;

  projector = new jake::jvColorHistogramProjection(n/3, n/3, n/3, n/3, n/3, 1);

  feat.derived().resize(pdata.cols() / 4, n);
  feat = Matrix<float, Dynamic, Dynamic>::Zero(pdata.cols() / 4, n);

  curr.resize(1, pdata.cols());
  for (i = 0; i < pdata.cols() / 4; i++) {
    for (j = i*4; j < (i+1) * 4; j++) {
      //curr(0, j) = pdata(0, j);
      if (j % 4 < 2) {
        curr(0, j) = ceil(pdata(0, j));
      }
      if (j % 4 > 1) {
        curr(0, j) = floor(pdata(0, j));
      }
    }

    /*curr(0, 0) = ceil(curr(0, 0));
    curr(0, 1) = ceil(curr(0, 1));
    curr(0, 2) = floor(curr(0, 2));
    curr(0, 3) = floor(curr(0, 3));*/

    cout << "Rows Cols of curr " << curr.rows() << " " << curr.cols() << endl;
    cout << "input frame" << endl;
    inputframe = img(Rect(curr(0, i*4 + 0), curr(0, i*4 + 1), curr(0, i*4 + 2), curr(0, i*4 + 3)));
    cout << "CURR IN FEATURE VECTOR "
         << curr(0, i*4 + 0) << " "
         << curr(0, i*4 + 1) << " "
         << curr(0, i*4 + 2) << " "
         << curr(0, i*4 + 3) << endl;
    cout << "CROP IN FEATURE VECTOR " << inputframe.rows << " " << inputframe.cols << endl;

    // This needs to be checked. It does not seem to work.
    // As in the ROI is not being extracted for histogramo computaion.
    image.reset(new jake::jvVideoFull(inputframe));

    projector->project(*(image.get()), imhist);

    // Collect Histogram
    hist = (jake::jvColorHistogramFeature *)imhist[0].get();

    // Normalize and collect histogram for each channel.
    sum = 1;
    for (l = 0; l < n/3; l++) {
      sum += hist->v[0].at(l);
    }
    for (l = 0; l < n/3; l++) {
      feat(i, l) = hist->v[0].at(l) / sum;
    }

    sum = 1;
    for (l = 0; l < n/3; l++) {
      sum += hist->v[1].at(l);
    }
    for (l = 0; l < n/3; l++) {
      feat(i, l + n/3) = hist->v[1].at(l) / sum;
    }

    sum = 1;
    for (l = 0; l < n/3; l++) {
      sum += hist->v[2].at(l);
    }
    for (l = 0; l < n/3; l++) {
      feat(i, l + 2*n/3) = hist->v[2].at(l) / sum;
    }
  }

  cout << "feat in feature_vector " << endl;
  for (int l = 0; l < feat.rows(); l++) {
    for (int m = 0; m < feat.cols(); m++)
      cout << feat(l, m) << " ";
    cout << endl;
  }

  cout << "Done normalizing the histogram" << endl;

  return;
}
