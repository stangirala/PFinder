/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    fusedetections.h
 * AUTHOR(S):   Sarma Tangirala (vtangira@buffalo.edu)
 * DESCRIPTION:
 *   Header file for fusedetections.cpp
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


template <typename D1, typename D2, typename D3>
void fusedetections(const MatrixBase<D1> &r, const MatrixBase<D1> &c, const MatrixBase<D2> &framedata, MatrixBase<D3> &framedata);
