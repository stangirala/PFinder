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
#include <string>

#include <jakeVideo.h>
#include <Eigen/Dense>

#include "hist_distance.h"
#include "utils.h"

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
double hist_distance(jake::jvVideo *VidHist1, jake::jvVideo *VidHist2, int bin, int type) {

  jake::jvColorHistogramProjection HistProj(bin, bin, bin, bin, bin, type);
  std::vector<std::shared_ptr<jake::jvVideoFeature>> VidFeature[2];
  jake::jvColorHistogramFeature *hist[2];
  Matrix<float, Dynamic, Dynamic> Diff;
  std::shared_ptr<class Log> log;
  log.reset(new class Log());
  std::stringstream strstream;


  log->log_msg ("Projecting Videos.");
  HistProj.setType(1);
  HistProj.project(*VidHist1, VidFeature[0]);
  HistProj.project(*VidHist2, VidFeature[1]);
  log->log_msg ("Done projecting videos.");

  hist[0] = (jake::jvColorHistogramFeature *)VidFeature[0][0].get();
  hist[1] = (jake::jvColorHistogramFeature *)VidFeature[1][0].get();

  strstream << "Histogram Size: " << VidFeature[0].size() << " Channel Size: " << hist[0]->v.size()
       << " 1st Bin Size: " << hist[0]->v[0].size() << endl;
  log->log_msg(strstream.str());


  /*Diff.resize(hist[0]->v.size(), hist[0]->v[0].size());
  for (int i = 0; i < hist[0]->v.size(); i++) {
    for (int j = 0; j < hist[0]->v[i].size(); j++) {

      Diff(i, j) = sqrt(hist[0]->v[i].at(j)) - sqrt(hist[1]->v[i].at(j));
    }
  }

  log->log_msg("Done with histogram calculation");

  return (1 - (Diff.norm())/sqrt(2));*/

  float sum = 0;
  for (int i = 0; i < hist[0]->v.size(); i++) {
    for (int j = 0; j < hist[0]->v[i].size(); j++) {
      sum += sqrt(hist[0]->v[i].at(j)) - sqrt(hist[1]->v[i].at(j));
    }
  }

  return (sqrt(sum)/sqrt(2));
}
