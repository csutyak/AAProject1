#include <iostream>
#include <fstream>
#include <string.h>

#include "fileLib.hpp"

#define MAXINPUT 256

int bfsFileParser(std::string filename, Graph* bfsGraph)
{
    const std::string FILENAME_PREFIX =  "../graphs/";
    std::string fullFilename = FILENAME_PREFIX + filename;

    std::ifstream inputStream;
    inputStream.open(fullFilename);
    if(inputStream.fail())
    {
        std::cout << "PLEASE ENTER A GOOD FILE :)";
        return -1;
    }

    char lineInput[MAXINPUT];
    char workingSubstring[MAXINPUT];
    int workingNodeValue;
    int lineCtr = 0;
    int lineIndex = 0;
    int workingLineIndex = 0;
    //indicates whether the value is a node or a weight
    bool nodeFlag = true;

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
                    bfsGraph->addEdge(lineCtr ,workingNodeValue);
                    std::cout << "Added connection: " << lineCtr << " " << workingNodeValue << std::endl; 
                }
                //weights would go here when needed (hint: else)
                if(nodeFlag)
                {
                    nodeFlag = false;
                }
                else
                {
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
}