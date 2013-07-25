/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    fusedetections.cpp
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Header-Only file, fuseddetections.cpp
 *
 ********************************************************************
 */

#include <vector>
#include <iostream>

#include <stdio.h>

#include <jakeVideo.h>
#include <Eigen/Dense>

#include "utils.h"

#pragma once

/** \file fusedetections.cpp
    \brief

    Fuses intersecting bounding boxes identifying an object. This is done by averaging them.

 */

template <typename D1, typename D2, typename D3>
void fusedetections(const MatrixBase<D1> &r, const MatrixBase<D1> &c, const MatrixBase<D2> &framedata, MatrixBase<D3> &framedet) {

  int grouplabel, i, j, k, l, emptycounter, mean, count;
  float sum;
  bool intersect;
  Matrix<float, Dynamic, Dynamic> tempdata, framedent, data;
  std::vector<std::vector<int> > groups;


  data.resize(4, framedata.cols() / 4);
  reshape(framedata, 4, framedata.cols() / 4, data);
  data.transpose();


  groups.push_back(vector<int>());
  groups[0].push_back(r(1, 0)); groups[0].push_back(c(1, 0));
  grouplabel = 0;
  intersect = false;
  for (i = 0; i < r.cols(); i++) {
    emptycounter = 0;
    for (j = 0; j <= grouplabel; j++) {

      // Find intersection of groups[j] and the current set of points
      for (k = 0; k < groups[j].size(); k++) {
        if (groups[j][k] == r(1, i) or groups[j][k] == c(1, i)) {

          // Either row or column have matched. Merge to current group.
          groups[j].push_back(r(1, i)); groups[j].push_back(c(1, i));

          sort(groups[j].begin(), groups[j].end());
          for (l = 1; l < groups[j].size(); l++) {
            if (groups[j][l - 1] == groups[j][l])
              groups[j].erase(groups[j].begin());
          }

          intersect = true;
          break;
        }
      }
      if (intersect != true) {
        // Create new group only if ???
        if (emptycounter == grouplabel) {
          grouplabel++;
          groups[grouplabel].push_back(r(1, i));
          groups[grouplabel].push_back(c(1, i));
        }
        else emptycounter++;
      }

      intersect = false;
    }
  }

  // Setup framedet using groups.
  framedet.derived().resize(1, groups.size() * 4);
  // Fuse loop.
  for (i = 0; i < groups.size(); i++) {
    sum = 0; count = 0;
    for (j = 0; j < groups[i].size(); j++) {
      sum += groups[i][j];
    }
    mean = sum / groups[i].size();
    // Check the bound here.
    for (j = i * 4; j < (i*4) + 4; j++) {
      framedet(1, j) = mean;
    }
  }

  return;
}
