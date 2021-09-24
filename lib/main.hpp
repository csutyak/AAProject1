#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <iomanip>
#include <string>

//Purpose: To obtain user input 
//Input: Nothing
//Output:
void greeting()
{
    //greeting
    std::cout << std::endl; 
    std::cout << "         ---  Welcome to the Flow Network Program  ---" << std::endl;
    std::cout << std::setw(26) << " " << "Written by:" << std::endl;
    std::cout << std::setw(25) << " " << "Cole & Taylor" << std::endl;
    std::cout << std::endl;
}

//Purpose: figure out user input about the type of graph needed to be created
//Input: From the commandline, recieve the filename, nodecount, and the purpose of the graph
//Output: A number representing the type of graph needed to be made
graphType createGraphGreeting(std::string const fileName, int nodeCount, std::string graphPurpose)
{
    if(nodeCount < 4) {
        throw "Graph needs to have 3 or more nodes";
    }

    if(!graphPurpose.compare("f"))
    {
        std::cout << "Creating graph for fulkerson purposes with " << nodeCount << " nodes to graph file named " << fileName << std::endl;
        return graphType::Fulkerson;
    }
    else if(!graphPurpose.compare("c"))
    { 
        std::cout << "Creating graph for circulation purposes with " << nodeCount << " nodes to graph file named " << fileName << std::endl;
        return graphType::Circulation;
    }
    else
    {
        throw "Graph purpose has bad formatting. Please look at README.txt for more information";
    }
}

#endif