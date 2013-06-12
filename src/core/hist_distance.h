/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    hist_distance.h
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Header files for hist_distance.c
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

double hist_distance(jake::jvVideo *, jake::jvVideo *);
