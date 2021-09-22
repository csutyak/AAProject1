#include "createGraph.hpp"

//configures file path
    const std::string FILENAME_PREFIX =  "../graphs/";
    std::string fullFilename = FILENAME_PREFIX + filename;
    std::ifstream inputStream;
    inputStream.open(fullFilename);