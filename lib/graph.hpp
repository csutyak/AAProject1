#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <vector>
#include <ctype.h>

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
    //generates graph from filename
    graph(std::string filename);
    ~graph();

    //adds and edge from the begin node to the end node of weight specificied
    void addEdge(int beginNode, int endNode, int weight);

    //if the node exists
    bool ifNode(int questionableNode);

    //outputs the graph to console
    void printGraph();

    //Finds shortest path using BFS
    bool BFS(int startNode, int endNode);
    //prints shortest path
    void printBFSPath(int endNode);

    //finds the max flow of a graph
    int FFMaxFlow();

    //finds the total weight of the graph
    int totalWeights();

private:
    //fills source node list with a list of source nodes
    void populateSourceNode();
    //sets the flow of all nodes to the value passed
    void setAllFlow(int value);
    //creates master nodes if there are more than 1 target and source node
    //otherwise sets the nodes to the default target and source node
    void findMasterNodes();
    //allocates more nodes to the memory structures necessary
    void allocateMoreNodes(int newNumNodes);
    //sets the set BFS path to the minimum cap
    int setMinimumCap();
    //add flow to the flow of the node
    void addFlow(int startNode, int endNode, int flow);
    //uses the flow of the nodes + capacity to create a residual graph
    void updateResidualGraph();

    int nodeCount;
    //array of vectors for each nodes data
    std::list<edge> *adjacencyList;

    std::list<int> *targetNodes;
    std::list<int> *sourceNodes;
    int masterTarget;
    int masterSource;

    //shortest path variables
    int* pred;
    int* dist;
};

#endif