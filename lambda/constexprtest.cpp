#include <iostream>

using namespace std;

constexpr int add(int a, int b)
{
    if (a > 0)
        return a + b;
    return b;
}

int global_var = 0;
constexpr int Increment(int n)
{
    // global_var++;
    return [n]
    { return n + 1; }();
}

constexpr int arraySize(int n)
{
    return n * 2;
}

// 상수표현식을 이용한 템플릿 인자 예시
template <int N>
struct Factorial
{
    static constexpr int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0>
{
    static constexpr int value = 1;
};

int main()
{
    int y = 32;
    // 컴파일 타임에 배열크기 정의 예시
    int arr[arraySize(5)];

    // constexpr (상수 표현식): C++11에서 도입된 키워드로 컴파일 타임에 그 값이 결정될 수 있는 표현식
    // 이점: 컴파일 타임 계산, 상수 표현식 보장, 최적화 기회
    // 제한사항: 단일 반환문(C++11 기준, 14부터 다중 반환 가능), 전역 상태 변경 금지, 상수 표현식에서 사용 가능한 연산만 사용
    auto answer = [y]() constexpr
    {
        int x = 10;
        return y + x;
    };

    int result = answer();
    // compile time에 result에 Inrement 함수 결과값이 정해짐
    result = Increment(result);

    cout << result << endl;

    constexpr int factorialResult = Factorial<5>::value;
    cout << factorialResult << endl;

    return 0;
}
