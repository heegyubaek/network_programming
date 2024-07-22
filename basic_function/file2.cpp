#include <iostream>
#include "global.h"

void modifyGlobalVar()
{
    globalVar = 20;
    std::cout << "Global Variable in file2: " << globalVar << std::endl;
}

int main()
{
    printGlobalVar();
    modifyGlobalVar();
    printGlobalVar();
    return 0;
}