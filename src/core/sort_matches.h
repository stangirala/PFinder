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
 *   Header File, sort_matches.h
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


#pragma once

/** \file sort_matches.h
    \brief

    Ranks detected hits and returns a "list" of size numhits.

 */

using namespace::cv;
using namespace::Eigen;
using namespace::std;

bool comparer (struct score_t a, struct score_t b);


void sort_matches(vector<struct score_t> &match_scores,
                  const int &num_hits,
                  vector<struct score_t> &hits);
