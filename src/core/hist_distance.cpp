/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    hist_distance.cpp
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Source file, hist_distance.cpp
 *
 ********************************************************************
 */


#include <math.h>
#include <vector>
#include <iostream>

#include <jakeVideo.h>
#include <Eigen/Dense>

#include "hist_distance.h"

/** \file   hist_distance.cpp
    \brief  Computes a distance metric
            between two histograms.

 */

/** \fn   long double hist_distance(hist1, hist2)
    \brief  Computes the Hellinger distance between
            two histograms.

    \parm VidHist1 jake::jvVideo object pointer representing the
                   data for histogram.
    \parm VidHist2 jake::jvVideo object pointer representing the
                   data for histogram.

    Computes Hellinger distance as the norm of the difference of the
    respective squared histogram values.
 */
double hist_distance(jake::jvVideo *VidHist1, jake::jvVideo *VidHist2) {

  jake::jvColorHistogramProjection HistProj;

  std::vector<std::shared_ptr<jake::jvVideoFeature>> VidFeature[2];

  jake::jvColorHistogramFeature *hist[2];

  Matrix<float, Dynamic, Dynamic> Diff;

  printf ("Projecting Videos.\n");
  HistProj.setType(1);
  HistProj.project(*VidHist1, VidFeature[0]);
  HistProj.project(*VidHist2, VidFeature[1]);
  printf ("Done projecting videos.\n");

  hist[0] = (jake::jvColorHistogramFeature *)VidFeature[0][0].get();
  hist[1] = (jake::jvColorHistogramFeature *)VidFeature[1][0].get();

  /*cout << "Histogram Size: " << VidFeature[0].size() << " Channel Size: " << hist[0]->v.size()
       << " 1st Bin Size: " << hist[0]->v[0].size() << endl;*/

  Diff.resize(hist[0]->v.size(), hist[0]->v[0].size());
  for (int i = 0; i < hist[0]->v.size(); i++) {
    for (int j = 0; j < hist[0]->v[i].size(); j++) {

      Diff(i, j) = hist[0]->v[i].at(j) - hist[1]->v[i].at(j);
      //printf ("%e\n", Diff(i, j));
    }
    //printf ("\n\n");
  }

  return (1 - (Diff.norm())/sqrt(2));
}
