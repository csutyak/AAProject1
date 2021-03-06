/*
    createGraph.hpp

    Declaration and implementation of functions to create a graph file
*/

#ifndef CREATEGRAPH_HPP
#define CREATEGRAPH_HPP

#include "graph.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//finds the node at the end of a specific layer
int nodeThreshold(int* layerArray, int currLayer) {

    int total = 0;

    for(int i = 0; i < currLayer + 1; ++i) {

        total += layerArray[i];
    }

    return total;
}

//generates both a regular graph and a circulation graph; depending on the flag
void generateGraph(int nodeCount, bool ifDemand, std::ofstream& file)
{
    //take square root of node count (round to int)= layers
    int layers = ceil(sqrt (nodeCount));
    //node count / number of layers = base layer number
    int avgNodeAmountInLayers = ceil(nodeCount / layers);
    //generating an array that holds the node count per layer of size layers
    int layerNodeCount [layers];

    //make the first and last layer 1 for the target and source
    layerNodeCount[0] = 1;
    layerNodeCount[layers - 1] = 1;

    //initialize total amount of nodes in each layer
    int totalNodes;

    do{
        totalNodes = 2;
        srand(time(NULL));

        //iterate through the nodeCount array
        for(int i = 1; i < layers - 2; ++i)
        {
            //randomnumber range = +-(layers / 2)
            int nodePerLayer = rand() % avgNodeAmountInLayers + (- (ceil(layers / 4)));
            
            //add that to the base layer number
            layerNodeCount[i] = avgNodeAmountInLayers + nodePerLayer;

            totalNodes += avgNodeAmountInLayers + nodePerLayer;
        }

        //the last number of array = nodeCount - all othber numbers in the array
        layerNodeCount[layers - 2] = nodeCount - totalNodes;

    } 
    //if nodeCount > count of all nodes in array then redo array calc.
    while(totalNodes > nodeCount);

    //nodes in the layer
    std::cout << "layer node count: ";
    for(int i = 0; i < layers; ++i) {
        std::cout << layerNodeCount[i] << "  ";
    }
    std::cout << std::endl;

    //find connections
    std::vector<int> pastConnections;

    //for the first node as the source
    //randomly picks many nodes the source will connect to
    int connectionAmount = rand() % layerNodeCount[1] + 1; 

    //add a demand if needed
    if (ifDemand)
    {
        file << (rand() % (-1) - 10) << " ";
    }

    //loop through to look at the next layer of to create connections
    for (int i = 0; i < connectionAmount; ++i) 
    {
        //pick a random node in the second layer 
        int randConnection = rand() % layerNodeCount[1] + 1;
  
        if (std::find(pastConnections.begin(), pastConnections.end(), randConnection) != pastConnections.end())
        {
            --i;
        }
        else 
        {
            //found a connection, add it to make sure not found again
            pastConnections.push_back(randConnection);

            file << randConnection << " " << (rand() % 50 + 1) << " ";
        }
    }

    file << std::endl;

    //for all the middle nodes
    int currLayer = 1;
    int currNodeThreshhold = 0;

    for(int i = 1; i < nodeCount - 1; ++i)
    {
        pastConnections.clear();

        currNodeThreshhold = nodeThreshold(layerNodeCount, currLayer);

        //used to pick the biggest node to connect to 
        if(i == currNodeThreshhold)
        {
            ++currLayer; 
        }

        //chooses the amount of connections from currNode
        ////randomnumber range from before + layers = amount of connections
        connectionAmount = rand() % layerNodeCount[currLayer + 1] + 1;

        //add demand of 0 if needed
        if (ifDemand)
        {
            file << 0 << " ";
        }
        
        //do those connections
        for(int j = 0; j < connectionAmount; ++j)
        {
            //pick a random node in the current or next layer 
            //select random amount of nodes based on randomnumber generated,
            int randConnection = rand() % (nodeThreshold(layerNodeCount, currLayer + 1) - i - 1) + (i + 1);
  
            //donot select node more than once
            if (std::find(pastConnections.begin(), pastConnections.end(), randConnection) != pastConnections.end()) {
                   
                --j;
            }
            else{

                pastConnections.push_back(randConnection);

                //weight is just random number from 1 - 20
                file << randConnection << " " << (rand() % 50 + 1) << " ";
            }
        }

        file << std::endl;

        currNodeThreshhold = 0;
    }

    //to account for the last node
    if(ifDemand)
    {
        file << rand() % 10 + 1 << std::endl;
    }
    else 
    {
        file << std::endl;
    }
}

//generates both a regular graph and a circulation graph; depending on the flag
void generateCapacityScalingGraph(int nodeCount, std::ofstream& file)
{
    //take square root of node count (round to int)= layers
    int layers = ceil(sqrt (nodeCount));
    //node count / number of layers = base layer number
    int avgNodeAmountInLayers = ceil(nodeCount / layers);
    //generating an array that holds the node count per layer of size layers
    int layerNodeCount [layers];

    //make the first and last layer 1 for the target and source
    layerNodeCount[0] = 1;
    layerNodeCount[layers - 1] = 1;

    //initialize total amount of nodes in each layer
    int totalNodes;

    do{
        totalNodes = 2;
        srand(time(NULL));

        //iterate through the nodeCount array
        for(int i = 1; i < layers - 2; ++i)
        {
            //randomnumber range = +-(layers / 2)
            int nodePerLayer = rand() % avgNodeAmountInLayers + (- (ceil(layers / 4)));
            
            //add that to the base layer number
            layerNodeCount[i] = avgNodeAmountInLayers + nodePerLayer;

            totalNodes += avgNodeAmountInLayers + nodePerLayer;
        }

        //the last number of array = nodeCount - all other numbers in the array
        layerNodeCount[layers - 2] = nodeCount - totalNodes;

    } 
    //if nodeCount > count of all nodes in array then redo array calc.
    while(totalNodes > nodeCount);

    //nodes in the layer
    std::cout << "layer node count: ";
    for(int i = 0; i < layers; ++i) {
        std::cout << layerNodeCount[i] << "  ";
    }
    std::cout << std::endl;

    //find connections
    std::vector<int> pastConnections;

    //for the first node as the source
    //randomly picks many nodes the source will connect to
    int connectionAmount = rand() % layerNodeCount[1] + 1; 

    //loop through to look at the next layer of to create connections
    for (int i = 0; i < connectionAmount; ++i) 
    {
        //pick a random node in the second layer 
        int randConnection = rand() % layerNodeCount[1] + 1;
  
        if (std::find(pastConnections.begin(), pastConnections.end(), randConnection) != pastConnections.end())
        {
            --i;
        }
        else 
        {
            //found a connection, add it to make sure not found again
            pastConnections.push_back(randConnection);
            
            int choice = rand() % 2;

            if(choice == 0)
            {
                file << randConnection << " " << (rand() % 2000 + 1000) << " ";
            }
            else
            {
                file << randConnection << " " << 1 << " ";
            }   
        }
    }

    file << std::endl;

    //for all the middle nodes
    int currLayer = 1;
    int currNodeThreshhold = 0;

    for(int i = 1; i < nodeCount - 1; ++i)
    {
        pastConnections.clear();

        currNodeThreshhold = nodeThreshold(layerNodeCount, currLayer);

        //used to pick the biggest node to connect to 
        if(i == currNodeThreshhold)
        {
            ++currLayer; 
        }

        //chooses the amount of connections from currNode
        ////randomnumber range from before + layers = amount of connections
        connectionAmount = rand() % layerNodeCount[currLayer + 1] + 1;
        
        //do those connections
        for(int j = 0; j < connectionAmount; ++j)
        {
            //pick a random node in the current or next layer 
            //select random amount of nodes based on randomnumber generated,
            int randConnection = rand() % (nodeThreshold(layerNodeCount, currLayer + 1) - i - 1) + (i + 1);
  
            //donot select node more than once
            if (std::find(pastConnections.begin(), pastConnections.end(), randConnection) != pastConnections.end()) {
                   
                --j;
            }
            else{

                pastConnections.push_back(randConnection);
                
                int choice = rand() % 2;

                if (choice == 0)
                {
                    file << randConnection << " " << (rand() % 2000 + 1000) << " ";
                }
                else
                {
                    file << randConnection << " " << 1 << " ";
                }
            }
        }

        file << std::endl;

        currNodeThreshhold = 0;
    }

    //to account for the last node
    file << std::endl;
}

//sets up the file creation and sets flag to determine the type of graph the user wants
void graphCreate(std::string filename, int nodeCount, graphType type)
{
    //configures file path
    const std::string FILENAME_PREFIX =  "../graphs/";
    std::string fullFilename = FILENAME_PREFIX + filename;
    std::ofstream outputStream;
    outputStream.open(fullFilename);

    //single source single target
    if(type == graphType::Fulkerson)
    {
        generateGraph(nodeCount, false, outputStream);
    }
    //demands with single source single target
    else if(type == graphType::Circulation)
    {
        generateGraph(nodeCount, true, outputStream);
    }
    else if(type == graphType::CapacityScaling)
    {
        generateCapacityScalingGraph(nodeCount, outputStream);
    }

    outputStream.close();
}

#endif
