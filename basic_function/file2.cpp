#include <iostream>
#include "global.h"

// Declare printf with C linkage.
extern "C" int printf(const char *fmt, ...);

//  Cause everything in the specified
//  header files to have C linkage.
extern "C"
{
    // add your #include statements here
#include <stdio.h>
}

//  Declare the two functions ShowChar
//  and GetChar with C linkage.
extern "C"
{
    char ShowChar(char ch);
    char GetChar(void);
}

//  Define the two functions
//  ShowChar and GetChar with C linkage.
extern "C" char ShowChar(char ch)
{
    putchar(ch);
    return ch;
}

extern "C" char GetChar(void)
{
    char ch;
    ch = getchar();
    return ch;
}

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
    printf("%c", ShowChar(GetChar()));
    return 0;
}