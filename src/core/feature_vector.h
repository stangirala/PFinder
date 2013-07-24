/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    hdetect_poselets.h
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Header file for feature_vector.cpp
 *
 ********************************************************************
 */


#pragma once

#include <vector>
#include <string>
#include <cmath>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <drwnBase.h>

#include <jakeVideo.h>
#include <Eigen/Dense>
#include <boost/filesystem.hpp>

#include "utils.h"

template <typename D1, typename D2>
void feature_vector(const MatrixBase<D1> &pdata, const cv::Mat &img, MatrixBase<D2> &feat);
