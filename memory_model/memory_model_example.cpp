#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> data(0);
std::atomic<bool> ready(false);

void producer()
{
    // Write data with relaxed ordering
    data.store(42, std::memory_order_relaxed);
    // Release, to make sure data is visible to consumer
    ready.store(true, std::memory_order_release);
}

void consumer()
{
    // Acquire, to make sure data is visible
    while (!ready.load(std::memory_order_acquire))
    {
        // Wait until ready is true
    }

    std::cout << "Data: " << data.load(std::memory_order_relaxed) << std::endl;
}

int main()
{
    /*
    - producer는 data를 42로 설정하고, ready를 true로 설정합니다.
    - ready를 memory_order_release로 설정하여, data에 대한 모든 이전 연산이 ready 설정 전에 완료되었음을 보장합니다.
    - consumer는 ready를 memory_order_acquire로 읽어들여, data가 42로 설정된 후 ready가 true로 설정되었음을 보장합니다.
     */

    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}

/*
올바른 메모리 모델을 이해한다는 것은:
멀티스레드 환경에서 변수의 읽기 및 쓰기 연산이 어떻게 상호작용하는지 이해하는 것.
메모리 가시성과 일관성을 유지하는 방법을 알고, 이를 적절히 사용하는 것.
성능 최적화와 일관성 간의 균형을 맞추는 방법을 아는 것을 의미합니다.
C++의 메모리 모델과 다양한 메모리 순서 옵션을 통해 이를 효과적으로 관리할 수 있습니다.

메모리 모델이란?
메모리 모델은 프로그래밍 언어에서 멀티스레드 프로그램의 동작을 정의하는 규칙 집합입니다.
이는 메모리 연산(읽기, 쓰기)의 순서가 어떻게 보장되고, 스레드 간의 메모리 가시성이 어떻게 유지되는지를 설명합니다.

C++ 메모리 모델
C++11부터 도입된 C++ 메모리 모델은 멀티스레드 프로그래밍에서의 동작을 명확히 정의합니다.
이는 두 가지 주요 요소로 나눌 수 있습니다:

1. 순차 일관성 (Sequential Consistency):
- 프로그램의 모든 연산이 정의된 순서대로 실행되는 것처럼 보입니다.
- 스레드 간의 연산 순서가 유지되어, 한 스레드의 변경이 다른 스레드에서 일관되게 관찰됩니다.

2. 메모리 순서 (Memory Order):
- C++11은 다양한 메모리 순서 옵션을 제공하여 성능 최적화와 일관성 간의 균형을 맞출 수 있도록 합니다.
- 대표적인 메모리 순서 옵션으로는 std::memory_order_relaxed, std::memory_order_consume, std::memory_order_acquire, std::memory_order_release, std::memory_order_acq_rel, std::memory_order_seq_cst가 있습니다.


주요 메모리 순서 옵션
1. memory_order_relaxed:
- 최소한의 메모리 순서 제약을 가집니다.
- 원자적 연산 자체의 원자성은 보장하지만, 다른 메모리 연산과의 순서는 보장하지 않습니다.
- 주로 성능 최적화에 사용됩니다.

2. memory_order_acquire:
- 이 연산 이후의 모든 읽기/쓰기 연산은 acquire 연산 이후에 일어납니다.
- 주로 플래그를 읽어 상태 변화를 감지하는 데 사용됩니다.

3. memory_order_release:
- 이 연산 이전의 모든 읽기/쓰기 연산은 release 연산 이전에 일어납니다.
- 주로 플래그를 설정하여 상태 변화를 알리는 데 사용됩니다.

4. memory_order_acq_rel:
- acquire와 release의 결합으로, 이전의 모든 연산이 완료된 후 연산이 수행되고, 이후의 모든 연산은 이 연산 이후에 수행됩니다.
- 주로 락을 구현할 때 사용됩니다.

5. memory_order_seq_cst:
- 모든 스레드가 동일한 순서로 메모리 연산을 관찰하도록 보장합니다.
- 가장 강력한 일관성 모델로, 디버깅과 유지보수에 유리하지만 성능 오버헤드가 큽니다.

 */