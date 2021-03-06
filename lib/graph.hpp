#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <vector>
#include <ctype.h>

enum class graphType
{
    Fulkerson, Circulation, CapacityScaling
};

class edge
{
public:
    edge(int Node, int Weight): 
        node(Node), weight(Weight){ flow = 0;}

    int node;
    int weight;
    int flow;
};

class graph
{
public:
    //constructor: generates graph from filename
    graph(std::string filename, graphType type);

    //constructor: generates empty graph from node count
    graph(int nodeCount);

    //destructor
    ~graph();

    //adds and edge from the begin node to the end node of weight specificied
    void addEdge(int beginNode, int endNode, int weight);

    //checks if the node exists
    bool ifNode(int questionableNode);

    //outputs the graph to console
    void printGraph();

    //Finds shortest path using BFS
    bool BFS(int startNode, int endNode);
    
    //prints shortest path
    void printBFSPath(int endNode);

    //finds the total edges of the graph
    int totalEdges();

    //finds the maxWeight of an edge in the graph
    int maxWeight();

    //finds the total weight of the graph
    int totalWeights();

    //finds the max flow of a graph
    int FFMaxFlow();

    //finds the circulation
    void solveCirculation(int& supply, int& demand);

    //finds the max flow of a graph using capacity scaling
    int capacityScalingFFMaxFlow();

private:
    int nodeCount;
    //array of vectors for each nodes data
    std::list<edge> *adjacencyList;
    graphType type;
    std::list<int> *targetNodes;
    std::list<int> *sourceNodes;
    int masterTarget;
    int masterSource;
    int* demandArray;
    int totalDemand;
    //shortest path variables for BFS
    int* pred;
    int* dist;

    inline void setMasterNodes(int v_masterSource, int v_masterTarget) 
        { masterTarget = v_masterTarget; masterSource = v_masterSource; }

    //sets the set BFS path to the minimum cap
    int setMinimumCap();

    //sets the flow of all nodes to the value passed
    void setAllFlow(int value);

    //uses the flow of the nodes + capacity to create a residual graph
    void updateResidualGraph();

    //fills source node list with a list of source nodes
    void populateSourceNode();

    //allocates more nodes to the memory structures necessary
    void allocateMoreNodes(int newNumNodes);

    //creates master nodes if there are more than 1 target and source node
    //otherwise sets the nodes to the default target and source node
    void findMasterNodes();

    //generate default fulkersonGraph
    void generateFulkersonGraph(std::string filename);

    //creates the master nodes for a circulation graph using demand
    void createCirculationMasterNodes();

    //generate graph circulation with weights
    void generateCirculationGraph(std::string filename);
};

#endif
