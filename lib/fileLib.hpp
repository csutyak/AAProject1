#ifndef FILELIB_HPP
#define FILELIB_HPP

#include <string>

#include "BFS.hpp"

//populate the BFS graph using the filename given
int bfsFileParser(std::string filename, Graph* bfsGraph);

#endif