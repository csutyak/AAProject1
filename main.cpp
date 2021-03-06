#include "createGraph.hpp"
#include "main.hpp"
#include "graph.hpp"

#include <iostream>
#include <string.h>

int main(int argc, char** argv)
{
    greeting();

    try
    {
        if(argc != 5 && argc != 3)
        {
            throw "format is ./main -option options";
        }
        //Breadth First Search
        if(strcmp(argv[1], "-b") == 0)
        {   
            if(argc != 5)
            {
                throw "-b must have the format ./main -b filename startnode endnode";
            }
            std::cout << "starting bfs implementation" << std::endl;
            graph bfsGraph(argv[2], graphType::Fulkerson);
            //bfsGraph.printGraph();
   
            if(bfsGraph.BFS(atoi(argv[3]), atoi(argv[4])))
            {
                bfsGraph.printBFSPath(atoi(argv[4]));
            }
            else
            {
                std::cout << "There is no shortest path!" << std::endl;
            }
        }
        //Ford-Fulkerson implementation
        else if(strcmp(argv[1], "-f") == 0)
        {
            if(argc != 3)
            {
                throw "-f must have the format ./main -f filename";
            }
            std::cout << "testing your Ford-Fulkerson implementation" << std::endl;
            graph bfsGraph(argv[2], graphType::Fulkerson);
            //bfsGraph.printGraph();

            int maxFlow =  bfsGraph.FFMaxFlow();
            std::cout << "Max Flow is: " << maxFlow << std::endl;
            //bfsGraph.printGraph();
        }
        //Circulation Problem
        else if(strcmp(argv[1], "-c") == 0)
        {
            if(argc != 3)
            {
                throw "-c must have the format ./main -c filename";
            }
            std::cout << "testing your application to the circulation problem" << std::endl;
            graph bfsGraph(argv[2], graphType::Circulation);
            //bfsGraph.printGraph();

            int maxFlow, demand;
            bfsGraph.solveCirculation(maxFlow, demand);
            if(maxFlow >= demand)
            {
                std::cout << "This graph has a circulation! " << std::endl;
                std::cout << "maxFlow: " << maxFlow << " Demand: " << demand << std::endl;
            }
            else
            {
                std::cout << "This graph does not have a circulation! " << std::endl;
                std::cout << "maxFlow: " << maxFlow << " Demand: " << demand << std::endl;
            }
        }
        //Capacity Scaling Flow Problem
        else if(strcmp(argv[1], "-cf") == 0)
        {
            if(argc != 3)
            {
                throw "-CF must have the format ./main -CF filename";
            }
            std::cout << "testing your application to the Capacity Scaling FF max flow problem" << std::endl;
            graph bfsGraph(argv[2], graphType::Fulkerson);
            //bfsGraph.printGraph();

            int maxFlow =  bfsGraph.capacityScalingFFMaxFlow();
            std::cerr << "Max Flow is: " << maxFlow << std::endl;
        }
        //graph creation for testing
        else if(strcmp(argv[1], "-g") == 0)
        {
            if(argc != 5)
            {
                throw "-g must have the format ./main -g filename nodeCount graphUse";
            }
            
            int nodeCount = std::stoi(argv[3]);

            graphType type = createGraphGreeting(argv[2], nodeCount, argv[4]);

            graphCreate(argv[2], nodeCount, type);

            std::cerr << "Finished. Please check the graph folder for your new graph!" << std::endl;
        }
    }
    catch(const char* exception)
    {
        std::cout << "ERROR: " << std::endl;
        std::cout << exception << std::endl;
    }
    return 0;
}
