#include "BFS.hpp"

void Graph::addEdge(int addNode, int connectingNode)
//precondition: 2 valid user nodes
//postcondition: add the edge into the graph vector
{
    //variables:
    int isHere = -1;

    //check if the node number is already in the graph structure
    for(std::size_t i = 0; i < knownNodes.size(); ++i)
    {
        if(knownNodes[i] == addNode)
        {
            isHere = i;
        }
    }

    if(isHere == -1)//not found, create new node and connection
    {
        GraphNode *newHead;
        GraphNode *newConnection;

        newHead = new GraphNode;
        newConnection = new GraphNode;

        //load the new nodes with the data
        newHead->nodeName = addNode;
        newConnection->nodeName = connectingNode;
        newHead->next = newConnection;
        newConnection->next = nullptr;

        //add to vectors
        knownNodes.push_back(addNode);
        connections.push_back(newHead);
    }
    else //node found, no need to create a new one
    {
        GraphNode *newFollowing;
        GraphNode *nodePtr;

        newFollowing = new GraphNode;
        newFollowing->nodeName = connectingNode;
        newFollowing->next = nullptr;

        nodePtr = connections[isHere];

        while (nodePtr->next) //find next available spot for new edge
        {
            nodePtr = nodePtr->next;
        }
        nodePtr->next = newFollowing;
    }
}

void Graph::bfs(int start, int startPlace, int endN)
{
    //variables
    std::queue<GraphNode*> depthQ;
    std::vector<int> path;
    bool endFound = false;
    bool found = false;

    //initialize queue & list
    connections[startPlace]->visited = true;
    depthQ.push(connections[startPlace]);

    do
    {
        GraphNode* nodePtr = depthQ.front();
        depthQ.pop();

        for(std::size_t i = 0; i < path.size(); ++i)
        {
            if(nodePtr->nodeName == path[i])
            {
                found = true;
            }
        }
        if (!found)
        {
            path.push_back(nodePtr->nodeName);
        }
        found = false;//reset

        if(nodePtr->nodeName == endN)
        {
            endFound = true;
            break;
        }
        int i = 0;
        while(found == false)
        {
            if(nodePtr->nodeName == connections[i]->nodeName)
            {
                nodePtr = connections[i];
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