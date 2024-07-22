#include <iostream>
#include "global.h"

void modifyGlobalVar()
{
    // 지역 변수로 동일한 변수명을 선언시, extern 선언한 globalVar은 변화가 없다.
    // int globalVar = 20;
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