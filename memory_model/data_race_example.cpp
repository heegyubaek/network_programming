#include <thread>
#include <iostream>
#include <mutex>

#define DATA_RACE_SOLUTION 1

int shared_data = 0;
#if DATA_RACE_SOLUTION
std::mutex mtx;
#endif

void increment()
{
    for (int i = 0; i < 100000; ++i)
    {
#if DATA_RACE_SOLUTION
        /*
        std::mutex를 사용하여 shared_data에 접근하는 부분을 보호하고 있습니다.
        std::lock_guard는 스코프 내에서 자동으로 mutex를 잠그고 스코프를 벗어나면 자동으로 해제합니다.
        이를 통해 데이터 레이스를 방지할 수 있습니다.
         */
        std::lock_guard<std::mutex> lock(mtx);
#endif
        ++shared_data;
    }
}

int main()
{
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final value: " << shared_data << std::endl;

    return 0;
}

/*
데이터 레이스의 정의
데이터 레이스는 다음과 같은 조건을 만족할 때 발생합니다:

동일한 메모리 위치: 두 개 이상의 스레드가 동일한 메모리 위치에 접근한다.
동시성: 접근하는 시점이 겹친다. 즉, 스레드 간에 동기화가 되어 있지 않다.
쓰기 작업: 접근 중 적어도 하나의 스레드가 쓰기 작업을 수행한다.


데이터 레이스: 두 개 이상의 스레드가 동시에 동일한 메모리 위치에 접근할 때, 적어도 하나의 스레드가 쓰기 작업을 수행하는 상황.
조건: 동일한 메모리 위치 접근, 동시성, 쓰기 작업 포함.
해결 방법: std::mutex와 같은 동기화 도구를 사용하여 스레드 간의 접근을 동기화.
 */