#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <iomanip>
#include <climits>

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

void outdated()
{
    int nodeCount;
    std::cin >> nodeCount;

    //validating user's input
    while (std::cin.fail() || nodeCount < 0 || nodeCount > 100)
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Invalid input. Must be a number." << std::endl;
        std::cout << "Amount of nodes in graph: "; 
        std::cin >> nodeCount;
    }

    //continue recieving input & organizing it
    //Graph flowGraph;
    for(int i = 0; i < nodeCount; i++)
    {
        std::string adjList;
        std::cout << "Adjacency List for node " << i << ": ";
        std::cin >> adjList;

        if(adjList.compare("0"))
        {
            //there are no outgoing edges from this node
            //flowGraph.addEdge(i, );
        }
        else
        {
            //read in the string and decifer between nodes and weights
            //should also check user input to make sure it is valid
            //flowGraph.addEdge(i, );
        }
    }
}

#endif