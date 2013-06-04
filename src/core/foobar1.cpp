/*******************************************************************
 * Project Core Files
 * Copyright (c) 2013, Jason Corso
 * All rights reserved.
 *
 *
 *******************************************************************
 * FILENAME:    foobar.cpp
 * AUTHOR(S):   Jason Corso (jcorso@buffalo.edu)
 *
 ********************************************************************
 */



#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <drwnBase.h>

#include "foobar1.h"

Foobar1::Foobar1() {

  foo++;
}

Foobar1::~Foobar1() {

  foo--;
}

void Foobar1::printSelfHello() {

  printf ("Foobar says Hello World!\n");
}
