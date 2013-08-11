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
  bool intersect;
  Matrix<float, Dynamic, Dynamic> tempdata, framedent, data;
  std::vector<std::vector<int> > groups;


  cout << "FUSE DETECTIONS FRAMEDATA " << endl << framedata << endl;

  data.resize(4, framedata.cols() / 4);
  reshape(framedata, 4, framedata.cols() / 4, data);
  cout << "FUSE DETECTIONS DATA AFTER RESHAPE" << endl << data << endl;
  data.transposeInPlace();

  cout << "FUSE DETECTIONS DATA AFTER TRANSPOSE" << endl << data << endl;

  groups.push_back(vector<int>());
  cout << "r VALUES" << endl << r << endl;
  cout << "c VALUES" << endl << c << endl;
  groups[0].push_back(r(0, 0)); groups[0].push_back(c(0, 0));
  grouplabel = 0;
  intersect = false;
  for (i = 0; i < r.cols(); i++) {
    emptycounter = 0;
    for (j = 0; j <= grouplabel; j++) {

      // Find intersection of groups[j] and the current set of points
      for (k = 0; k < groups[j].size(); k++) {
        if (groups[j][k] == r(0, i) or groups[j][k] == c(0, i)) {

          // Either row or column have matched. Merge to current group.
          groups[j].push_back(r(0, i)); groups[j].push_back(c(0, i));

          sort(groups[j].begin(), groups[j].end());
          /*for (l = 1; l < groups[j].size(); l++) {
            if (groups[j][l - 1] == groups[j][l])
              groups[j].erase(groups[j].begin());
          }*/
          l = 0;
          while (l < groups[j].size() - 1) {
            if (groups[j][l] == groups[j][l + 1])
              groups[j].erase(groups[j].begin() + l + 1);
            else l++;
          }

          intersect = true;
          break;
        }
      }
      if (intersect != true) {
        // Create new group only if ???
        if (emptycounter == grouplabel) {
          grouplabel++;
          groups[grouplabel].push_back(r(0, i));
          groups[grouplabel].push_back(c(0, i));
        }
        else emptycounter++;
      }

      intersect = false;
    }
  }

  cout << "SETUP GROUPS" << endl;

  for (i = 0; i < groups.size(); i++) {
    for (j = 0; j < groups[i].size(); j++)
      cout << groups[i][j] << " ";
    cout << endl;
  }

  cout << "FRAME DATA R, C " << data.rows() << " " << data.cols() << endl;

  // Setup framedet using groups.
  /*float sum;
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
      framedet(0, j) = mean;
    }
  }*/
  // Setup framedet using groups.
  framedet.derived().resize(1, groups.size() * 4);
  framedet.derived().setZero(framedet.rows(), framedet.cols());
  // Fuse loop.
  for (i = 0; i < groups.size(); i++) {

    //Matrix<float, groups[i].size(), data.cols()> tempmat;
    // Make a record of interesting detections.
    Matrix<float, Dynamic, Dynamic> tempmat;
    tempmat.resize(groups[i].size(), data.cols());
    for (j = 0; j < groups[i].size(); j++) {
      for (k = 0; k < data.cols(); k++)
        tempmat(j, k) = data(groups[i][j], k);
    }

    cout << "i value " << i << endl;

    //Matrix<float, 1, tempmat.cols()> sum;
    Matrix<float, Dynamic, Dynamic> sum;
    sum.resize(1, tempmat.cols());
    sum.setZero(sum.rows(), sum.cols());
    for (j = 0; j < tempmat.cols(); j++) {
      for (k = 0; k < tempmat.rows(); k++) {
        sum(0, j) += tempmat(k, j);
      }
      sum(0, j) /= tempmat.rows();
    }

    cout << "Setup framedet i value " << i << endl;

    for (j = 0; j < sum.cols(); j++)
     framedet(0, i*4 + j) = sum(0, j);
  }

  return;
}
