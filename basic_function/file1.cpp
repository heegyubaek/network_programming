#include <iostream>
#include "global.h"

int globalVar = 10;

void printGlobalVar()
{
    std::cout << "Global Variable in file1: " << globalVar << std::endl;
}