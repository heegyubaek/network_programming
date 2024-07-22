#ifndef GLOBAL_H
#define GLOBAL_H

extern int globalVar;

// C++에서 함수의 선언은 기본적으로 외부에서 정의된다는 의미를 내포하고 있음
// extern 키워드를 추가하나 안하나 동일한 효과를 가짐
void printGlobalVar();

#endif