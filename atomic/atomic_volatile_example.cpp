#include <iostream>
#include <thread>
#include <atomic>

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