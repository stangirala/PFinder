#include <math.h>
#include <vector.h>

#include <jvVideoProjection.h>

#include "hist_distance.h"

/** \file   hist_distance.cpp
    \brief  Computes the distance
            between two histograms.

*/

/** \fn   long double hist_distance(hist1, hist2)
    \brief  Computes the difference between the bin
            bin counts of two histograms
*/
std::shared_pointer<jvVideoFeature> long double hist_distance(jake::jvVideo VidHist1, jake::jakeVideo VidHist2) {

  std::shared_ptr<jvColorHistrogramProjection> ColoHistProj;
  std::vector<std::shared_ptr<jvVideoFeature>> VidFeature[2];
  std::shared_prt<jvVideoFeature> Diff;
  auto histitr1, histitr2;

  VidHist1.ExtractRGBHistogram(hist1, VidFeature[0]);
  VidHist2.ExtractRGBHistogram(hist1, VidFeature[1]);

  for (
        histitr1 = VidFeature[0].begin(), histitr2 = VidFeature[1].begin();
        hisitr1 != VidFeature[0].end(), hisitr2 != VideFeature[1].end;
        hsiitr1++; histitr2++;
      ) {

          Diff.push_back(histitr1 - histitr2);
  }

  return Diff;
}
