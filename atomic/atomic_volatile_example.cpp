#include <iostream>
#include <thread>
#include <atomic>

/* 'volatile'은 멀티스레드 환경에서 변수의 원자성을 보장하지 않음.
    즉, 변수의 일기-쓰기 작업이 중간에 끼어들 수 있는 상황을 막지 못함.
    이를 위해서는 추가적으로 'std::atomic'을 사용해야함 */
/* 'volatile'는 변수의 값을 매전 읽어오거나 기록하도록 강제하지만, 변수의
    변경을 감지하기 위해서는 올바른 메모리 모델을 이해하고 있어야 함.
    멀리스레드 프로그래밍에서 메모리 가시성 문제를 해결하기 위해서는
    'std::atomic'또는 적절한 메모리 배리어를 사용해야 함 */
// volatile int counter = 0;
std::atomic<int> counter(0);

void incrementCounter()
{
    for (int i = 0; i < 1000000; ++i)
    {
        ++counter;
    }
}

int main()
{
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}