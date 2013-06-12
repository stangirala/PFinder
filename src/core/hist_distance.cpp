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

  //auto histitr1, histitr2;
  Matrix<float, Dynamic, Dynamic> Diff;
  double score;

  printf ("Projecting first video.\n");
  HistProj.setType(1);
  HistProj.project(*VidHist1, VidFeature[0]);
  printf ("Projecting first video. Done\n");
  /*HistProj.project(*((const jake::jvVideo *)VidHist2), VidFeature[1]);
  printf ("Projecting second video. Done")*/

  cout << "Size: " << VidFeature[0].size() << endl; //<< " " << VidFeature[1].size() << endl;

  //VidFeature[0][0]->print();

  /*Diff = new Matrix<float, 1, VidFeature[0].size() + VidFeature[1].size()>::Zero(1, VidFeature[0].size() + VideFeature[1].size());

  i = 0;
  for (
        histitr1 = VidFeature[0].begin(), histitr2 = VidFeature[1].begin();
        hisitr1 != VidFeature[0].end(), hisitr2 != VideFeature[1].end;
        hsiitr1++; histitr2++;
      ) {

          Diff(i) = (sqrt(histitr1) - sqrt(histitr2));

          i++;
  }*/

  return score;
}
