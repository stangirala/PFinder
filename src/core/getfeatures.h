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
 *   Header-Only file, getfeature.cpp
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

#include "test_feature.h"
#include "hdetect_poselets.h"
#include "feature_vector.h"
#include "fusedetections.h"

#pragma once

/** \file getfeature.cpp
    \brief

    \arg1 image file  The image input that is considered.
    \arg2 thresh  Threshold value.
    \arg3 scale The scaling on the process.
    \arg4 A vector containing persondata.
    \arg5 A vector containing features.

    Obtains features using the poselet detectors for
    humans persons.
    Returns a list of feature values and persondata.

 */

using namespace::cv;
using namespace::Eigen;

template <typename D1, typename D2>
void getfeatures(boost::filesystem::path impath, float thresh, float scale, MatrixBase<D1> &persondata, MatrixBase<D2> &feat) {

  int i, j, size;
  float areafracthresh;
  Matrix<float, Dynamic, Dynamic> modifiedcurrentbox, areamat, areavec, areasum, pascalratiomat;
  Matrix<int, 1, Dynamic > r, c;
  Mat img;


  // Load the image.
  img = imread(impath.string(), CV_LOAD_IMAGE_COLOR);
  // bicubic interpolation.
  resize(img, img, cvSize(0, 0), 1, 1, INTER_CUBIC);

  // Detect poselets from the image.
  // if you are passing around filename then they are boostfs path objects.
  // persondata is established in this call.
  cout << "Detecting Poselets " << endl;
  hdetect_poselets(impath, thresh, scale, persondata);
  cout << "Done detecting Poselets" << endl;

  areafracthresh = 0.4;

  // Identify a region as a person using the poselet.
  cout << "persondata cols and rows " << persondata.cols() << persondata.rows() << endl;
  if (persondata.cols() != 0 || persondata.rows() != 0) {
    if (persondata.cols() > 4) {
      modifiedcurrentbox.resize(4, persondata.cols() / 4);
      for (j = 0; j < persondata.cols() / 4; j++) {
        for (i = 0; i < 4; i++) {
          modifiedcurrentbox(i, j) = persondata(i, j);
        }
      }

      cout << "Setting up Modified Currentbox" << endl;

      modifiedcurrentbox.transpose();

      alignedRectInt(modifiedcurrentbox, modifiedcurrentbox, areamat);

      cout << "Calculating Rectint" << endl;

      /**********Check this***********/
      size = (((persondata.cols() - 3) % 4) + 1);
      areavec.resize(1, size);
      for (i = 0; i < size; i++) {
        areavec(0, i) = persondata(0, i) * persondata(0, i+1);
      }

      cout << "Setup areavec" << endl;


      Matrix<float, Dynamic, Dynamic> temp1, temp2;
      repmat(areavec, areamat.rows(), 1, temp1);
      repmat(areavec.transpose(), 1, areamat.rows(), temp2);

      cout << "Calculating repmat" << endl;

      areasum = temp1 + temp2;


      for (i = 0; i < areasum.rows(); i++) {
        for (j = 0; j < areasum.cols(); j++) {
          pascalratiomat(i, j) = areasum(i, j) / (areasum(i, j) - areamat(i, j));
        }
      }

      Matrix<float, Dynamic, Dynamic> temp;
      // Along the same dimension?
      temp = pascalratiomat.triangularView<Eigen::Upper>();
      for (i = 0; i < temp.rows(); i++) {
        for (j = 0; j < temp.cols(); j++) {
          if (temp(i, j) > areafracthresh) {
            r.resize(1, r.cols() + 1);
            r(1, r.cols() - 1) = i;

            c.resize(1, c.cols() + 1);
            c(1, c.cols() - 1) = j;
          }
        }
      }

      if (r.cols() != 0) {
        // framedet is a column vector.
        Matrix<float, 1, Dynamic> framedet;
        fusedetections(r, c, persondata, framedet);
        persondata = framedet;
      }
    }

  // Setup Bounds checking here.

    cout << "Setting up feature vector" << endl;
    feature_vector(persondata, img, feat);
    cout << "Done setting up feature vector" << endl;
  }

  return;
}
