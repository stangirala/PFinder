/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    test_feature.cpp
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Source file, test_feature.cpp
 *
 ********************************************************************
 */

#include <vector>
#include <iostream>

#include <stdio.h>

#include <jakeVideo.h>
#include <Eigen/Dense>

#include "test_feature.h"

/** \file test_feature.cpp
    \brief Extracts features from an input image. Returns a vector of features.

    \arg1 jake::jvVideo *InputFrame Pointer to a test image whose
                                    object we are tracking.

 */

void feature_vector(jake::jvVideo *InputFrame, Matrix<float, 1, Dynamic> &feat) {

  int n, i, j, featindex, sum;

  std::shared_ptr<jake::jvColorHistogramProjection> HistProj;
  std::vector<std::shared_ptr<jake::jvVideoFeature>> VidFeature;
  jake::jvColorHistogramFeature *Histogram;

  n = 30;
  feat.resize(1, n);

  HistProj.reset(new jake::jvColorHistogramProjection(n/3, n/3, n/3, n/3, n/3, n/3));

  HistProj->setType(1);
  HistProj->project(*InputFrame, VidFeature);

  Histogram = (jake::jvColorHistogramFeature *) VidFeature[0].get();

  featindex = 0;
  printf ("before normalizing\n\n");
  // For each channel
  for (i = 0; i < 3; i++) {

    sum = 0;
    // Bin values for a channel.
    for (j = 0; j < Histogram->v[i].size(); j++) {
      sum += Histogram->v[i].at(j);
      feat(featindex + j) = Histogram->v[i].at(j);
      cout << feat(featindex + j) << " ";
    }
    cout << endl;

    // Normalize
    for (j = 0; j < Histogram->v[i].size(); j++) {
      feat(featindex + j) /= sum;
    }

    featindex += Histogram->v[i].size();
  }
}
