#include <iostream>
#include <string.h>

#include "main.hpp"
#include "graph.hpp"

int main(int argc, char** argv)
{
    greeting();

    try
    {
        if(strcmp(argv[1], "-b") == 0)
        {
            std::cout << "starting bfs implementation" << std::endl;
            graph bfsGraph(argv[2]);
            bfsGraph.printGraph();

            //Checks to see if source node is even in graph
            if(bfsGraph.ifNode(atoi(argv[3]))){
                
                //Checks to see if target node is even in graph
                if(bfsGraph.ifNode(atoi(argv[4]))){
                    
                    if(bfsGraph.BFS(atoi(argv[3]), atoi(argv[4])))
                    {
                        bfsGraph.printBFSPath(atoi(argv[4]));
                    }
                }
                else{
                    std::cout << "Second argument node is not in current graph - please try again" << std::endl;
                }
            }
            else{
                std::cout << "First argument node is not in current graph - please try again" << std::endl;
            }
        }
        else if(strcmp(argv[1], "-f") == 0)
        {
            std::cout << "testing your Ford-Fulkerson implementation" << std::endl;
        }
        else if(strcmp(argv[1], "-c") == 0)
        {
            std::cout << "testing your application to the circulation problem" << std::endl;
        }
    }
    catch(const char* exception)
    {
        std::cout << "ERROR" << std::endl;
        std::cout << exception << std::endl;
    }
    return 0;
}