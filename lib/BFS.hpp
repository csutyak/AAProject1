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
    Graph();

    struct GraphNode
    {
        int nodeName;
        bool visited = false;
        GraphNode* next;
    };
    GraphNode* head;

    std::vector<int>knownNodes;
    std::vector<GraphNode*> connections;
    
    void addEdge(int, int);
    void bfs(int, int, int);
};

#endif