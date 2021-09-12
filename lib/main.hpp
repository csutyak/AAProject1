#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <iomanip>

//Purpose: To obtain user input 
//Input: Nothing
//Output:
void greeting()
{
    //greeting
    std::cout << std::endl; 
    std::cout << "         ---  Welcome to the Flow Network Program  ---" << std::endl;
    std::cout << std::setw(26) << " " << "Written by:" << std::endl;
    std::cout << std::setw(25) << " " << "Cole & Taylor" << std::endl;
    std::cout << std::endl;
}

#endif