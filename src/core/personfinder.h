#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <ostream>
#include <iostream>

#include <drwnBase.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/lexical_cast.hpp>

#pragma once

#include "utils.h"

namespace boostfs = boost::filesystem;


typedef enum codes {
  BADARGS = 1,
  PATHARG,
  IMTYPEARG,
  VIDTYPEARG,
  TESTIMARG,
  INDEXIMG,
  INDEXVID,
  CLEANUP
};


extern "C" {
int personfinder (int argc, char **argv, boostfs::path &tempdir, std::vector<std::string> &paths_to_files, std::vector<std::string> &image_type, std::vector<struct score_t> &matches);

int closing_time(boostfs::path tempdir, std::vector<std::string> paths_to_files, std::vector<std::string> image_type);
}
