#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <iomanip>
#include <climits>

//Purpose: To obtain user input 
//Input: Nothing
//Output:
void greetingInput()
{
    //greeting
    std::cout << std::endl; 
    std::cout << "         ---  Welcome to the Flow Network Program  ---" << std::endl;
    std::cout << std::setw(26) << " " << "Written by:" << std::endl;
    std::cout << std::setw(25) << " " << "Cole & Taylor" << std::endl;
    std::cout << std::endl;

    //input
    int nodeCount = 0;
    std::cout << std::setw(21) << " " << "--- INSTRUCTIONS ---" << std::endl;
    std::cout << "  The input is very specific for this program. First, you will be" << std::endl;
    std::cout << "asked to provide how many nodes are in the graph. After that, you" <<std::endl;
    std::cout << "will be asked to provide an adjaceny list for each of those nodes." <<std::endl;
    std::cout << "The format for that will be the notation of the node, then the" <<std::endl;
    std::cout << "weight of the connection. For example, an input might look like" <<std::endl;
    std::cout << "the following for the example graph: " << std::endl; 
    std::cout << std::setw(2) << " " << "INPUT GRAPH:   0 <-10- 1" << std::endl;
    std::cout << std::setw(2) << " " << "               0 --3-> 1" <<std::endl;
    std::cout << "Amount of nodes in graph: 2" << std::endl;
    std::cout << "Adjacency List for node 0: 1 10" << std::endl;
    std::cout << "Adjacency List for node 1: 0 3" << std::endl;
    std::cout << "*** If there is no outgoing edge from a node, enter 0 ***" << std::endl;
    std::cout << std::endl;
    std::cout << "Amount of nodes in graph: ";
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


//Purpose: to obtain the users input on figuring which nodes need to be found for the shortest path
//Input: accepts graph object and the user chose this function
//Output: validates user input and calls graph function to find shortest path
void shortestPath(Graph& graph)
{
    //variables:
    int start;
    int startPlace;
    int endN;
    bool isThere = false;

    std::cout << "Please enter the starting node value: ";
    std::cin >> start;
    //check if the input is an actual node
    for(std::size_t i = 0; i < graph.knownNodes.size(); ++i)
    {
        if(graph.knownNodes[i] == start)
        {
            isThere = true;
            startPlace = i;
            break;
        }
    }
    //if not, ask again and validate user input
    while(isThere != true)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Please input a valid user node." << std::endl <<
             "Please enter the starting node value: ";
        std::cin >> start;

        for(std::size_t i = 0; i < graph.knownNodes.size(); ++i)
        {
            if(graph.knownNodes[i] == start)
            {
                isThere = true;
                startPlace = i;
                break;
            }
        }
    }


    std::cout << "Please enter the ending node value: ";
    std::cin >> endN;
    //check if the input is an actual node
    isThere = false;
    for(std::size_t i = 0; i < graph.knownNodes.size(); ++i)
    {
        if(graph.knownNodes[i] == endN)
        {
            isThere = true;
            break;
        }
    }
    //if not, ask again and validate user input
    while(isThere != true)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Please input a valid user node." << std::endl <<
             "Please enter the starting node value: ";
        std::cin >> start;

        for(std::size_t i = 0; i < graph.knownNodes.size(); ++i)
        {
            if(graph.knownNodes[i] == endN)
            {
                isThere = true;
                break;
            }
        }
    }
    std::cout << std::endl;

    graph.bfs(start, startPlace, endN); //call to necessary function
}

#endif