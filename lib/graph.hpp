#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <vector>

class edge
{
public:
    edge(int Node, int Weight): 
        node(Node), weight(Weight){}

    int node;
    int weight;
};

class graph
{
public:
    //generates graph from filename
    graph(std::string filename);
    ~graph();

    //adds and edge from the begin node to the end node of weight specificied
    void addEdge(int beginNode, int endNode, int weight);

    bool ifNode(int questionableNode);

    void printGraph();

    bool BFS(int startNode, int endNode);
    void printBFSPath(int endNode);

    int totalWeights();

private:
    int nodeCount;
    //array of vectors for each nodes data
    std::list<edge> *adjacencyList;

    //shortest path variables
    int* pred;
    int* dist;
};

#endif