#ifndef BFS_HPP
#define BFS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>

class Graph
{
public:
    inline Graph(){};

    struct GraphNode
    {
        int nodeName;
        bool visited = false;
        GraphNode* next;
    };
    GraphNode* head;

    std::vector<int>knownNodes;
    std::vector<GraphNode*> connections;
    
    void addEdge(int addNode, int connectingNode);
    void bfs(int start, int startPlace, int endN);
};

void shortestPath(Graph& graph);

#endif