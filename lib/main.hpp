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
int createGraphGreeting(std::string const fileName, std::string const nodeCount, std::string graphPurpose)
{
    int graphType = 0;

    if(!graphPurpose.compare("b"))
    {
        graphPurpose = "breadth first search with a single source and single target";
        graphType = 1;
    }
    else if(!graphPurpose.compare("f"))
    {
        graphPurpose = "ford fulkerson with multiple sources and multiple targets";   
        graphType = 2;
    }
    else if(!graphPurpose.compare("c"))
    {
        graphPurpose = "circulation problem with demands";
        graphType = 3;
    }
    else if(!graphPurpose.compare("cf"))
    {
        graphPurpose = "capacity scaling";
        graphType = 4;
    }
    else
    {
        throw "Graph purpose has bad formatting. Please look at README.txt for more information";
    }

    std::cout << "Creating graph for " << graphPurpose << " purposes with " << nodeCount << " nodes to graph file named " << fileName << std::endl;

    return graphType;
}

#endif