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
  Matrix<int, 1, Dynamic> r, c;
  Mat img;


  // Load the image.
  img = imread(impath.string(), CV_LOAD_IMAGE_COLOR);
  if (!img.data) {
    cout << "Unable to open " << impath.string() << endl;
  }
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

      int k = 0;
      for (j = 0; j < persondata.cols() / 4; j++) {
        for (i = 0; i < 4; i++) {
          modifiedcurrentbox(i, j) = persondata(0, k);
          k++;
        }
      }


      cout << "MODIFIED CURRENT BOX" << endl << modifiedcurrentbox << endl;
      cout << "SIZE " << modifiedcurrentbox.rows() << " " << modifiedcurrentbox.cols() << endl;
      modifiedcurrentbox.transposeInPlace();


      cout << "rectint" << endl;

      alignedRectInt(modifiedcurrentbox, modifiedcurrentbox, areamat);

      cout << "Calculating Rectint" << endl;

      /**********Check this***********/
      /*size = (((persondata.cols() - 3) % 4) + 1);
      areavec.resize(1, size);
      for (i = 0; i < size; i++) {
        areavec(0, i) = persondata(0, i + 3) * persondata(0, i + 4);
      }*/
      size = ceil((persondata.cols() - 3.0) / 4);
      areavec.resize(1, size);
      for (i = 0; i < size; i++) {
        areavec(0, i) = persondata(0, i*4 + 2) * persondata(0, i*4 + 3);
      }

      cout << "Setup areavec" << endl;


      Matrix<float, Dynamic, Dynamic> temp1, temp2;
      cout << "AREAVEC SIZE " << areavec.rows() << " " << areavec.cols() << endl;
      cout << "AREAMAT SIZE " << areamat.rows() << " " << areamat.cols() << endl;
      repmat(areavec, areamat.rows(), 1, temp1);
      cout << "FIRST REPMAT. SIZE " << temp1.rows() << " "  << temp1.cols() << endl;
      areavec.transposeInPlace();
      repmat(areavec, 1, areamat.rows(), temp2);
      cout << "SECOND REPMAT. SIZE " << temp2.rows() << " " << temp2.cols() << endl;

      cout << "Calculating repmat" << endl;

      areasum = temp1 + temp2;

      cout << "areasum" << endl;

      pascalratiomat.resize(areasum.rows(), areasum.cols());
      for (i = 0; i < areasum.rows(); i++) {
        for (j = 0; j < areasum.cols(); j++) {
          pascalratiomat(i, j) = areasum(i, j) / (areasum(i, j) - areamat(i, j));
        }
      }

      cout << "pascal ration" << endl;

      Matrix<float, Dynamic, Dynamic> temp;
      // Triangular view one above the central diagonal.
      // Ugh. No bound checking.
      std::vector<int> vr, vc;
      for (i = 0; i < pascalratiomat.rows(); i++) {
        for (j = i + 1; j < pascalratiomat.cols(); j++) {
          if (pascalratiomat(i, j) > areafracthresh) {
            vr.push_back(i);
            vc.push_back(j);
          }
        }
      }
      r.resize(1, r.size());
      c.resize(1, c.size());
      for (i = 0; i < r.cols(); i++) {
        r(1, i) = vr[i]; c(1, i) = vc[i];
      }

      cout << "the r matrix" << endl;

      if (r.cols() != 0) {
        Matrix<float, 1, Dynamic> framedet;
        fusedetections(r, c, persondata, framedet);
        persondata = framedet;
      }
    }

    cout << "fuse this shit" << endl;

    // Setup Bounds checking here.

    cout << "Setting up feature vector" << endl;
    cout << "PDATA BEING SENT TO FEATURE_VECTOR " << persondata.rows() << " " << persondata.cols ()
          << endl << persondata << endl
          << "image path being read " << impath.string() << endl;
    feature_vector(persondata, img, feat);
    cout << "Done setting up feature vector" << endl;
  }

  return;
}
