#include <iostream>
using namespace std;

union RecordType
{
    char ch;
    int i;
    long l;
    float f;
    double d;
    int *int_ptr;
};

int main()
{
    RecordType t;

    /* union의 모든 멤버는 동일한 메모리 위치를 공유합니다.
    어느 때라도 union의 멤버 중 하나만 활성 상태여야 합니다.
    union은 가장 큰 멤버를 저장하는 데 필요한 메모리만 사용합니다. */
    t.f = 7.25;
    t.i = 5;

    /* 64bit system에서는 pointer가 8바이트, long 8, float 4, double 8
    32bit system에서는 pointer 4, long 4, float 4, double 8 */
    cout << sizeof(t) << endl;
    cout << t.i << endl;
    // union의 각 멤버는 동일한 메모리 위치를 공유하므로, 하나의 멤버에 값을 저장하면
    // 다른 멤버의 값이 덮어써짐
    // 아래처럼 둘 이상을 동시에 사용하려고 하면 데이터 손상이 발생할 수 있음
    cout << t.f << endl;
}
