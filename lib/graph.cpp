#include "graph.hpp"

#define MAXINPUT 65536
#define INT_MAX 999999

graph::graph(std::string filename)
{
    std::cout << "creating graph" << std::endl;
    const std::string FILENAME_PREFIX =  "../graphs/";
    std::string fullFilename = FILENAME_PREFIX + filename;

    std::ifstream inputStream;
    inputStream.open(fullFilename);
    if(inputStream.fail())
    {
        throw "PLEASE ENTER A GOOD FILENAME :)";
    }

    //for counting the number of nodes
    std::ifstream inputStream2;
    inputStream2.open(fullFilename);

    char lineInput[MAXINPUT];
    char workingSubstring[MAXINPUT];
    int workingNodeValue;
    int lineCtr = 0;
    int lineIndex = 0;
    int workingLineIndex = 0;
    int workingConnectionValue = 0;
    //indicates whether the value is a node or a weight
    bool nodeFlag = true;

    //count amount of nodes in the file
    nodeCount = 0;
    while(inputStream2.getline(lineInput,MAXINPUT))
    {
        ++nodeCount;
    }

    adjacencyList = new std::list<edge>[nodeCount];

    pred = new int[nodeCount];
    dist = new int[nodeCount];
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < nodeCount; i++) 
    {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    //loops through file
    while(inputStream.getline(lineInput,MAXINPUT))
    {
        char space = ' ';
        strncat(lineInput, &space, 1);
        lineIndex = 0;
        //while the line isnt ended
        nodeFlag = true;
        while(lineInput[lineIndex]  != '\0')
        {
            //if it finds a space
            if(lineInput[lineIndex] == ' ')
            { 
                workingSubstring[workingLineIndex] = '\0';
                workingNodeValue = atoi(workingSubstring);
                if(nodeFlag)
                {
                    workingConnectionValue = workingNodeValue;
                    nodeFlag = false;
                }
                else
                {
                    addEdge(lineCtr, workingConnectionValue, workingNodeValue);
                    nodeFlag = true;
                }

                workingLineIndex = -1;
            }
            else
            {
                workingSubstring[workingLineIndex] = lineInput[lineIndex];
            }
            ++workingLineIndex;
            ++lineIndex;
        }
        ++lineCtr;
    }

    inputStream2.close();
    inputStream.close();

    std::cout << "Graph created" << std::endl;
}

graph::~graph()
{
    delete[] adjacencyList;
    delete[] pred;
    delete[] dist;
}

void graph::addEdge(int beginNode, int endNode, int weight)
{
    adjacencyList[beginNode].push_back(edge(endNode, weight));
}

//This function will check to see if a node is in the graph or not
bool graph::ifNode(int questionableNode)
{
    bool ifThere = false;

    for(int i = 0; i < nodeCount; ++i){
        
        for(const auto& node : adjacencyList[i]){
            if (node.node == questionableNode){
                ifThere = true;
                break;
            }
        }
    }

    return ifThere;
}

void graph::printGraph()
{
    std::cout << "Node count: " << nodeCount << std::endl;
    for(int i = 0; i < nodeCount; ++i)
    {
        for(const auto& node : adjacencyList[i])
        {
            std::cout << i << " -> " << node.node << " weight " << node.weight <<std::endl;
        }
        
    }
}

bool graph::BFS(int startNode, int endNode) 
{
    //checks to make sure arguments are in the graph
    if(ifNode(startNode) && ifNode(endNode)) {

        std::cerr << "starting BFS" << std::endl;
        // a queue to maintain queue of vertices whose
        // adjacency list is to be scanned as per normal
        // DFS algorithm
        std::list<int> queue;
 
        // boolean array visited[] which stores the
        // information whether ith vertex is reached
        // at least once in the Breadth first search
        bool* visited = new bool[nodeCount];

        for (int i = 0; i < nodeCount; i++) 
        {
             visited[i] = false;
        }
 
        // now source is first to be visited and
        // distance from source to itself should be 0
        visited[startNode] = true;
        dist[startNode] = 0;
        queue.push_back(startNode);
 
        // standard BFS algorithm
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop_front();
            for(const auto& node : adjacencyList[u])
            {
                if (visited[node.node] == false) 
                {
                    visited[node.node] = true;
                    dist[node.node] = dist[u] + 1;
                    pred[node.node] = u;
                    queue.push_back(node.node);
 
                    // We stop BFS when we find destination
                    if (node.node == endNode){
                        return true;
                    }
                }
            }
        }

        delete[] visited;
    
        std::cout << "False lol";
        return false;
    }
    else{
        std::cout << "At least one of the argument nodes are not in this graph. Please try again." << std::endl;
        return false;
    }
}

void graph::printBFSPath(int endNode)
{
    std::cerr << "Printing BFSPAth" << std::endl;
    // vector path stores the shortest path
    std::vector<int> path;
    int crawl = endNode;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
 
    // distance from source is in distance array
    std::cout << "Shortest path length is : "<< dist[endNode];
 
    // printing path from source to destination
    std::cout << "\nPath is:" << std::endl;
    for (int i = path.size() - 1; i >= 0; i--)
    {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;
}