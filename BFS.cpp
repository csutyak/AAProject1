#include <iostream>
#include <vector>
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

void Graph::bfs(int start, int startPlace, int endN)
{
    //variables
    std::queue<FollowNode*> depthQ;
    std::vector<int> path;
    bool endFound = false;
    bool found = false;

    followers[startPlace]->visited = true;
    depthQ.push(followers[startPlace]);

    do
    {
        FollowNode* nodePtr = depthQ.front();
        depthQ.pop();

        for(std::size_t i = 0; i < path.size(); ++i)
        {
            if(nodePtr->user == path[i])
            {
                found = true;
            }
        }
        if (!found)
        {
            path.push_back(nodePtr->user);
        }
        found = false;//reset

        if(nodePtr->user == endN)
        {
            endFound = true;
            break;
        }
        int i = 0;
        while(found == false)
        {
            if(nodePtr->user == followers[i]->user)
            {
                nodePtr = followers[i];
                found = true;
            }
            ++i;
        }
        found = false;

        while(nodePtr != nullptr)
        {
            if(nodePtr->visited == false)
            {
                depthQ.push(nodePtr);
                nodePtr->visited = true;
            }
            nodePtr = nodePtr->next;
        }
    }
    while(endFound == false || !depthQ.empty());

    if(endFound == true)
    {
        std::cout << "The shortest path is: ";
        std::size_t i;
        for(i = 0; i < path.size() - 1; ++i)
        {
            std::cout << path[i] << " -> ";
        }
        std::cout << path[i] << std::endl << std::endl;
    }
    else
    {
        std::cout << "There is no path from user " << start << " to " << endN << std::endl << std::endl;
    }
}

int main(int argc, char** argv)
{
    return 0;
}