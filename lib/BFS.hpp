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

    struct graphNode
    {
        int user;
        bool visited = false;
        graphNode* next;
    };
    graphNode* head;

    std::vector<int>follow;
    std::vector<graphNode*> followers;

    void addEdge(int, int);
    void bfs(int, int, int);
};

#endif