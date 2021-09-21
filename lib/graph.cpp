#include "graph.hpp"

#define MAXINPUT 65536
#define INT_MAX 999999

graph::graph(std::string filename, graphType Type)
{
    type = Type;

    if(type == graphType::Fulkerson)
    {
        generateFulkersonGraph(filename);
    }
    else if(type == graphType::Circulation)
    {
        generateCirculationGraph(filename);
    }
}

void graph::generateFulkersonGraph(std::string filename)
{
    //configures file path
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

    demandArray = nullptr;

    //loops through file
    targetNodes = new std::list<int>;
    sourceNodes = new std::list<int>;
    while(inputStream.getline(lineInput,MAXINPUT))
    {
        if(!isdigit(lineInput[0]))
        {
            targetNodes->push_back(lineCtr);
        }
        else
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
        }
        ++lineCtr;
    }

    inputStream2.close();
    inputStream.close();
    setAllFlow(0);
    populateSourceNode();
}

void graph::generateCirculationGraph(std::string filename)
{
    std::cout << "generating circulation graph" << std::endl;
    //configures file path
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
    int nodeDemandValue = 0;
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

    demandArray = new int[nodeCount];
    totalDemand = 0;

    //loops through file
    targetNodes = new std::list<int>;
    sourceNodes = new std::list<int>;
    while(inputStream.getline(lineInput,MAXINPUT))
    {
        char space = ' ';
        strncat(lineInput, &space, 1);
        lineIndex = 0;

        while(lineInput[lineIndex] != ' ')
        {
            workingSubstring[lineIndex] = lineInput[lineIndex];
            ++lineIndex;
        }
        workingSubstring[lineIndex] = '\0';
        //set the demand per node to the first value
        demandArray[lineCtr] = atoi(workingSubstring);
        ++lineIndex;
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
    setAllFlow(0);
}

graph::~graph()
{
    delete[] adjacencyList;
    delete[] pred;
    delete[] dist;

    //delete targetNodes;
    if(sourceNodes != nullptr)
    {
        delete sourceNodes;
        delete targetNodes;
    }

    if(demandArray != nullptr)
    {
        delete[] demandArray;
    }
}

void graph::addEdge(int beginNode, int endNode, int weight)
{
    //check and see if edge exists first
    for(auto& node : adjacencyList[beginNode])
    {
        if(node.node == endNode)
        {
            node.weight += weight;
            return;
        }
    }
    //if edge doesnt exist then create a new one
    adjacencyList[beginNode].push_back(edge(endNode, weight));
}

bool graph::ifNode(int questionableNode)
{
    if(questionableNode >= 0 && questionableNode <= nodeCount -1)
    {
        return true;
    }
    return false;
}

void graph::printGraph()
{
    std::cout << "Node count: " << nodeCount << std::endl;
    for(int i = 0; i < nodeCount; ++i)
    {
        for(const auto& node : adjacencyList[i])
        {
            std::cout << i << " -> " << node.node << " weight " << node.weight << " Flow " << node.flow << std::endl;
        }
    }

    if(demandArray != nullptr)
    {
        std::cout << "Demand List:" << std::endl;
        for(int i = 0; i < nodeCount; ++i)
        {
            std::cout << "node " << i << ": " << demandArray[i] << std::endl;
        }
    }
}

bool graph::BFS(int startNode, int endNode) 
{
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < nodeCount; i++) 
    {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    //checks to make sure arguments are in the graph
    if(ifNode(startNode) && ifNode(endNode)) 
    {
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
        while (!queue.empty()) 
        {
            int u = queue.front();
            queue.pop_front();
            for(const auto& node : adjacencyList[u])
            {
                if (visited[node.node] == false) 
                {
                    if(node.weight != 0)
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
        }
        delete[] visited;
        return false;
    }
    else{
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
    while (pred[crawl] != -1) 
    {
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

int graph::totalWeights()
{
    int total = 0;

    for(int i = 0; i < nodeCount; ++i)
    {
        for(const auto& node : adjacencyList[i])
        {
            total += node.weight;
        }
    }

    return total;
}

void graph::populateSourceNode()
{
    bool* foundArray = new bool[nodeCount];
    for(int i = 0; i < nodeCount; ++i)
    {
        foundArray[i] = false;
    }

    for(int i = 0; i < nodeCount; ++i)
    {   
        for(const auto& node : adjacencyList[i])
        {
            if(!foundArray[node.node])
            {
                 foundArray[node.node] = true;
            }
        }
    }

    for(int i = 0; i < nodeCount; ++i)
    {
        if(!foundArray[i])
        {
            sourceNodes->push_back(i);
        }
    }
    
    delete[] foundArray;
}

int graph::FFMaxFlow()
{
    //set the masterNode values
    if(type == graphType::Fulkerson)
    {
        findMasterNodes();
    }
    else
    {
        createCirculationMasterNodes();
    }
    setAllFlow(0);

    int maximumCapacity = 0;
    //use BFS to find shortest path
    while(BFS(masterSource, masterTarget))
    {
        //set flow to the minimum cap of the path
        maximumCapacity += setMinimumCap();
        updateResidualGraph();
    }
       
    return maximumCapacity;
    //find residual network 
}

void graph::setAllFlow(int value)
{
    for(int i = 0; i < nodeCount; ++i)
    {
        for(auto& node : adjacencyList[i])
        {
            node.flow = value;
        }
    }
}

void graph::findMasterNodes()
{
    //if there is only one source node make it the master
    if(sourceNodes->size() == 1)
    {
        masterSource = sourceNodes->front();
    }
    //if there is only one target node make it the master
    if(targetNodes->size() == 1)
    {
        masterTarget = targetNodes->front();
    }

    //if both target and source nodes need a new master allocate 2 nodes
    if(targetNodes->size() > 1 && sourceNodes->size() > 1)
    {
        allocateMoreNodes(2);
    }
    //if only one needs a new master allocate 1 node
    else if(targetNodes->size() > 1 || sourceNodes->size() > 1)
    {
        allocateMoreNodes(1);
    }

    //generate master source node
    if(sourceNodes->size() > 1)
    {
        if(targetNodes->size() > 1)
        {
            masterSource = nodeCount - 2;
        }
        else
        {
            masterSource = nodeCount - 1;
        }
        for(const auto& node : *sourceNodes)
        {
            addEdge(masterSource, node, INT_MAX);
        }
    }
    //generate master target node
    if(targetNodes->size() > 1)
    {
        masterTarget = nodeCount - 1;

        for(const auto& node : *targetNodes)
        {
            addEdge(node ,masterTarget, INT_MAX);
        }
    }
}

void graph::allocateMoreNodes(int newNumNodes)
{
    nodeCount += newNumNodes;

    delete[] pred;
    pred = new int[nodeCount];

    delete[] dist;
    dist = new int[nodeCount];
    
    std::list<edge> *oldAdjacencyList = adjacencyList;
    adjacencyList = new std::list<edge>[nodeCount];
    for(int i = 0; i < nodeCount - newNumNodes; ++i)
    {
        for(const auto& node : oldAdjacencyList[i])
        {
            addEdge(i, node.node, node.weight);
        }
        
    }
    delete[] oldAdjacencyList;

    if(demandArray != nullptr)
    {
        int* newDemandArray = new int[nodeCount];
        for(int i = 0; i < nodeCount - newNumNodes; ++i)
        {
            newDemandArray[i] = demandArray[i];
        }
        for(int i = nodeCount-newNumNodes; i < nodeCount; ++i)
        {
            newDemandArray[i] = 0;
        }
        delete[] demandArray;
        demandArray = newDemandArray;
    }
}

int graph::setMinimumCap()
{
    // vector path stores the shortest path
    std::vector<int> path;
    int crawl = masterTarget;
    path.push_back(crawl);
    while (pred[crawl] != -1) 
    {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
 
    // printing path from source to destination
    int minimumValue = INT_MAX; 
    //path[i]
    for (int i = path.size() - 2; i >= 0; i--)
    {
        for(const auto& node : adjacencyList[path[i + 1]])
        {
            if(node.node == path[i])
            {
                if(minimumValue > node.weight)
                {
                    minimumValue = node.weight;
                }
                break;
            }
        }
    }

    for (int i = path.size() - 2; i >= 0; i--)
    {
        for(auto& node : adjacencyList[path[i + 1]])
        {
            if(node.node == path[i])
            {
                node.flow += minimumValue;
                break;
            }
        }
    }
    return minimumValue;
}

void graph::updateResidualGraph()
{
    //loop through each edge
    int reverseWeight = 0;
    bool foundNode = false;
    for(int i = 0; i < nodeCount; ++i)
    {
        for(auto & node : adjacencyList[i])
        {
            if(node.flow != 0)
            {
                reverseWeight = node.flow;
                node.weight = node.weight - node.flow;
                node.flow = 0;
                for(auto & endNode : adjacencyList[node.node])
                {
                    if(endNode.node == i)
                    {
                        endNode.weight = reverseWeight;
                        endNode.flow = 0;
                        foundNode = true;
                    }
                }
                if(!foundNode)
                {
                    addEdge(node.node, i, reverseWeight);
                }
            }
        }
    } 
}

graph::graph(int v_nodeCount)
{
    nodeCount = v_nodeCount;
    adjacencyList = new std::list<edge>[nodeCount];

    pred = new int[nodeCount];
    dist = new int[nodeCount];

    sourceNodes = nullptr;
    targetNodes = nullptr;
}

int graph::capacityScalingFFMaxFlow()
{
    findMasterNodes();

    //find the highest number that is a factor of 2
    int workingMaxWeight = maxWeight();
    std::cerr << "max weight: " << workingMaxWeight << std::endl;
    int delta = 2;

    while(delta < workingMaxWeight)
    {
        delta *= 2;
    }
    delta = delta / 2; 
    std::cerr << "delta " << delta << std::endl;

    graph workingGraph(nodeCount);
    workingGraph.setMasterNodes(masterSource, masterTarget);
    int maxFlow = 0;
    while(delta >= 1)
    {
        for(int i = 0; i < nodeCount; ++i)
        {
            for(const auto& node : adjacencyList[i])
            {
                if(node.weight >= delta && node.weight < delta * 2)
                {
                    workingGraph.addEdge(i, node.node, node.weight);
                }
            }
        }
        //use BFS to find shortest path
        while(workingGraph.BFS(masterSource, masterTarget))
        {
            //set flow to the minimum cap of the path
            maxFlow += workingGraph.setMinimumCap();
            workingGraph.updateResidualGraph();
        }
        delta = delta / 2;
    }

    return maxFlow;
}

int graph::maxWeight()
{
    int maxWeight = 0;

    for(int i = 0; i < nodeCount; ++i)
    {
        for(const auto& node : adjacencyList[i])
        {
            if(node.weight > maxWeight)
            {
                maxWeight = node.weight;
            }
        }
    }

    return maxWeight;
}

void graph::createCirculationMasterNodes()
{
    //loop through the demand array
    //all negative are source and all positive are sink
    for(int i = 0; i < nodeCount; ++i)
    {
        if(demandArray[i] < 0)
        {
            sourceNodes->push_back(i);
        }
        else if(demandArray[i] > 0)
        {
            totalDemand += demandArray[i];
            targetNodes->push_back(i);
        }
    }

    if(sourceNodes->size() == 0 || targetNodes->size() == 0)
    {
        throw "there must be at least 1 source or target node";
    }

    allocateMoreNodes(2);

    //create master source node
    masterSource = nodeCount - 2;
    for(const auto& node : *sourceNodes)
    {
        addEdge(masterSource, node, demandArray[node] * -1);
    }

    //create master target node
    masterTarget = nodeCount - 1;
    for(const auto& node : *targetNodes)
    {
        addEdge(node, masterTarget, demandArray[node]);
    }
}

void graph::solveCircultion(int& supply, int& demand)
{
    supply = FFMaxFlow();
    demand = totalDemand;
}
