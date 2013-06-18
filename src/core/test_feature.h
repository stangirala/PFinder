/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    sort_match.h
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Header file for sort_match.cpp
 *
 ********************************************************************
 */


#pragma once

#include <vector>
#include <string>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <drwnBase.h>

#include <jakeVideo.h>

void feature_vector(jake::jvVideo *, Matrix<float, 1, Dynamic> &);
