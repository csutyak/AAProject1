#include <iostream>
#include <string.h>

#include "BFS.hpp"
#include "main.hpp"
#include "fileLib.hpp"

int main(int argc, char** argv)
{
    greeting();

    if(strcmp(argv[1], "-b") == 0)
    {
        Graph* bfsGraph = new Graph;
        bfsFileParser(argv[2], bfsGraph);
        int startnode = atoi(argv[3]);
        int startingNode = atoi(argv[3]);
        int endNode = atoi(argv[4]);

        std::cout << startnode << " " << startingNode << " " << endNode << std::endl;
        bfsGraph->bfs(startnode, startingNode, endNode);

        delete bfsGraph;
    }
    else if(strcmp(argv[1], "-f") == 0)
    {
        std::cout << "testing your Ford-Fulkerson implementation" << std::endl;
    }
    else if(strcmp(argv[1], "-c") == 0)
    {
        std::cout << "testing your application to the circulation problem" << std::endl;
    }
    return 0;
}