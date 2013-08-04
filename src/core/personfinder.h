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

namespace boostfs = boost::filesystem;


int personfinder (int argc, char **argv, boostfs::path &tempdir, std::vector<std::string> &paths_to_files, std::vector<std::string> &image_type);

int closing_time(boostfs::path tempdir, std::vector<std::string> paths_to_files, std::vector<std::string> image_type);
