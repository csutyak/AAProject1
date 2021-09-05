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
        GraphNode *newConnection;
        GraphNode *nodePtr;

        newConnection = new GraphNode;
        newConnection->nodeName = connectingNode;
        newConnection->next = nullptr;

        nodePtr = connections[isHere];

        while (nodePtr->next) //find next available spot for new edge
        {
            nodePtr = nodePtr->next;
        }
        nodePtr->next = newConnection;
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
    //THIS LINE IS GIVING A SEG FAULT
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