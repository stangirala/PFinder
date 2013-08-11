/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    hdetect_poselets.cpp
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Source File, sort_matches.cpp
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

#include "sort_matches.h"


/** \file sort_matches.cpp
    \brief

    Ranks detected hits and returns a "list" of size numhits.

 */

using namespace::cv;
using namespace::Eigen;
using namespace::std;

bool comparer (struct score_t a, struct score_t b) {
  return a.match>b.match?true:false;
}

void sort_matches(vector<struct score_t> &match_scores,
                  const int &num_hits,
                  vector<struct score_t> &hits) {

  int temp;

  cout << "THING BEFORE SORTING IN SORT_MATCHES" << endl;
  for (vector<struct score_t>::iterator itr = hits.begin(); itr != hits.end(); itr++)
    cout << " " << itr->match << " " << itr->path << endl;


  std::sort(match_scores.begin(), match_scores.end(), comparer);

  cout << "THE SORTING HAS BEEN DONE " << endl << endl;
  for (vector<struct score_t>::iterator itr = match_scores.begin(); itr != match_scores.end(); itr++)
    cout << itr->match << " ";
  cout << endl << endl;

  // Save into hits
  if (match_scores.size() < num_hits) {
    cout << "Number of detects is fewer than the num_hits ranking parameter." << endl;
    temp = match_scores.size();
  }
  else {
    temp = num_hits;
  }

  for (int i = 0; i < temp; i++) {
    cout << "Detection #" << match_scores[i].frame << " " << match_scores[i].match << " " << match_scores[i].path << " " << match_scores[i].type << endl
         << match_scores[i].box << endl;
  }

  return;
}
