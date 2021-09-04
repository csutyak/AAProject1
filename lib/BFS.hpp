#ifndef BFS_HPP
#define BFS_HPP

#include <iostream>
#include <vector>
#include <queue>

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

    struct FollowNode
    {
        int user;
        bool visited = false;
        FollowNode* next;
    };
    FollowNode* head;

    std::vector<int>follow;
    std::vector<FollowNode*> followers;

    void addEdge(int, int);
    void bfs(int, int, int);
};

#endif