#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename C>
void print(const string &s, const C &c)
{
    cout << s;

    for (const auto &e : c)
    {
        cout << e << " ";
    }

    cout << endl;
}

void fillVector(vector<int> &v)
{
    static int nextValue = 1;
    generate(v.begin(), v.end(), []
             { return nextValue++; });
}

int main()
{
    const int elementCount = 9;

    vector<int> v(elementCount, 1);

    int x = 1;
    int y = 1;

    // Lambda식에 mutable을 추가함으로써, capture로 value를 받는 x, y에 접근 할 수 있게 하고
    // Lambda식 내에서는 값을 유지하되, 밖에 있는 x, y값은 그 값을 그대로 유지하게 한다.
    // mutable이 없고 capture절을 & 참조로 변경하면 x,y 원본 값도 변경된다.
    generate_n(v.begin() + 2, elementCount - 2, [=]() mutable throw()->int {
        int n = x+y;
        x = y;
        y = n;
        return n; });

    print("vector v after call to generate_n() with lambda: ", v);

    cout << "x: " << x << "y: " << y << endl;

    fillVector(v);
    print("vector v after 1st call to fillVector(): ", v);

    fillVector(v);
    print("vector v after 2nd call to fillVector(): ", v);
}