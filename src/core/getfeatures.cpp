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


void getfeature(std::string impath, float thresh, float scale, Matrix<float, Dynamic, Dynamic> persondata, std::vector<float> &feat) {

  int i, j;
  float areafracthresh;
  Matrix<float, dynamic, dynamic> modifiedcurrentbox, areamat;


  // Image_dude read(impath)


  // img is a thingy that contains the image of impath.
  // this will have to be cv_mat.
  hdetect_poselet(impath, thresh, scale, persondata, img)

  areafracthresh = 0.4;

  if (persondata.cols() != 0) {

    if (persondata.size() > 4) {

      modifiedcurrentbox.resize(4, persondata.cols() / 4);
      for (j = 0; j < persondata.cols() / 4; j++) {
        for (i = 0; i < 4; i++) {
          modifiedcurrentbox.at(i, j) = persondata.at(i, j);
        }
      }

      modifiedcurrentbox.transpose();

      alignedRectInt(modifiedcurrentbox, modifiedcurrentbox, areamat);

      // modifiedcurrentbox is a Matrix that represents a rectangle.


    }

  }


  // feature_vector(persondata, img)

}
