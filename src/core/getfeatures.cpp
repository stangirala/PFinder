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
 *   Source file, getfeature.cpp
 *
 ********************************************************************
 */

#include <vector>
#include <iostream>

#include <stdio.h>

#include <jakeVideo.h>
#include <Eigen/Dense>

#include "test_feature.h"
#include "utils.h"
#include "fusedetections.h"

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


using namespace::Eigen;
using namespace::cv;

void getfeature(std::string impath, float thresh, float scale, Matrix<float, Dynamic, Dynamic> persondata, std::vector<float> &feat) {

  int i, j, size;
  float areafracthresh;
  Matrix<float, Dynamic, Dynamic> modifiedcurrentbox, areamat, areavec, areasum, pascalratiomat;
  Matrix<int, 1, Dynamic > r, c;
  Mat img;


  // Load the image.
  img = imread(impath, CV_LOAD_IMAGE_COLOR);

  // Detect poselets from the image.
  hdetect_poselet(img, thresh, scale, persondata2)

  areafracthresh = 0.4;

  // Identify a region as a person using the poselet.
  if (persondata.cols() != 0) {
    if (persondata.size() > 4) {
      modifiedcurrentbox.resize(4, persondata.cols() / 4);
      for (j = 0; j < persondata.cols() / 4; j++) {
        for (i = 0; i < 4; i++) {
          modifiedcurrentbox(i, j) = persondata(i, j);
        }
      }

      modifiedcurrentbox.transpose();

      alignedRectInt(modifiedcurrentbox, modifiedcurrentbox, areamat);

      /**********Check this***********/
      size = (((persondata.cols() - 3) % 4) + 1);
      areavec.resize(1, size);
      for (i = 0; i < size; i++) {
        areavec(0, i) = persondata(0, i) * persondata(0, i+1);
      }


      Matrix<float, Dynamic, Dynamic> temp1, temp2;
      repmat(areavec, areamat.rows(), 1, temp1);
      repmat(areavec.transpose(), 1, areamat.rows(), temp2);

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
        // Fix this.
        // framedet is a column vector.
        Matrix<float, 1, Dynamic> framedet;
        fusedetections(r, c, persondata, framedet);
        persondata = framedet;
      }
    }

    // Fix this.
    feat = feature_vector(persondata, img);
  }

  return;
}
