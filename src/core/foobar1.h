/*******************************************************************
 * Project Core Library
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    foobar.h
 * AUTHOR(S):   Jason Corso (jcorso@buffalo.edu)
 * DESCRIPTION: 
 *   Classes and functions related to the foobar core functionality.
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


class Foobar1 {

public:
    int foo;

    Foobar1();
    ~Foobar1();

    void printSelfHello();
};
