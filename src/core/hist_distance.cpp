#include <math.h>
#include <vector>
#include <iostream>

#include <jakeVideo.h>
#include <Eigen/Dense>

#include "hist_distance.h"

/** \file   hist_distance.cpp
    \brief  Computes the distance
            between two histograms.

*/

/** \fn   long double hist_distance(hist1, hist2)
    \brief  Computes the Hellinger difference between
            two histograms
    \arg jvVideo Objects reprsenting the histograms to be captured.
*/
double hist_distance(jake::jvVideo *VidHist1, jake::jvVideo *VidHist2) {

  jake::jvColorHistogramProjection HistProj;

  std::vector<std::shared_ptr<jake::jvVideoFeature>> VidFeature[2];

  jake::jvColorHistogramFeature *hist[2];

  std::vector<jake::jvColorHistogramFeature>::iterator histitr1, histitr2;

  printf ("Projecting Videos.\n");
  HistProj.setType(1);
  HistProj.project(*VidHist1, VidFeature[0]);
  HistProj.project(*VidHist2, VidFeature[1]);
  printf ("Done projecting videos.\n");

  hist[0] = (jake::jvColorHistogramFeature *)VidFeature[0][0].get();
  hist[1] = (jake::jvColorHistogramFeature *)VidFeature[1][0].get();

  /*cout << "Histogram Size: " << VidFeature[0].size() << " Channel Size: " << hist[0]->v.size()
       << " 1st Bin Size: " << hist[0]->v[0].size() << endl;*/

  MatrixXf Diff(hist[0]->v.size(), hist[0]->v[0].size());
  for (int i = 0; i < hist[0]->v.size(); i++) {
    for (int j = 0; j < hist[0]->v[i].size(); j++) {

      Diff(i, j) = hist[0]->v[i].at(j) - hist[1]->v[i].at(j);
      //printf ("%e\n", Diff(i, j));
    }
    //printf ("\n\n");
  }

  return (1 - (Diff.norm())/sqrt(2));

}
