#ifndef CREATEGRAPH_HPP
#define CREATEGRAPH_HPP

#include "graph.hpp"

#include <iostream>
#include <string>
#include <fstream>

void graphCreate(std::string filename, int nodeCount, graphType type)
{
    //configures file path
    const std::string FILENAME_PREFIX =  "../graphs/";
    std::string fullFilename = FILENAME_PREFIX + filename;
    std::ofstream inputStream;
    inputStream.open(fullFilename);

    //single source single target
    if(type == graphType::Fulkerson)
    {
        //create a graph
        //write to a file
        
    }
    //demands with single source single target
    else if(type == graphType::Circulation)
    {

    }

}

void singleSourceTargetGraph()
{
    
}

//input a graph into file
void writeFile(std::fstream filename, graph inputGraph, int nodeCount, bool isDemand)
{
    //no need to account for demand
    if(isDemand = false)
    {
        //no need to include demands

        //write to file
        for(int i = 0; i < nodeCount; ++i)
        {
            //for(const auto& node : inputGraph.adjacencyList[i])
            {
                //filename << node.node << " " << node.weight << " ";
            }

            filename << std::endl;
        }
    }
    //need to worry about demand
    else
    {
        //write to file
        for(int i = 0; i < nodeCount; ++i)
        {
            //filename << adjacencyList[i].demand;

            //for(const auto& node : inputGraph.adjacencyList[i])
            {
                //filename << " " << node.node << " " << node.weight << " ";
            }

            filename << std::endl;
        }
    }
}

#endif
