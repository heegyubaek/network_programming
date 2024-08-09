/* Rule 19.1: 매크로 정의의 제한
    매크로 정의는 코드의 복잡성을 높일 수 있기 때문에 제한적으로 사용해야 함
 */

#include <stdio.h>

#define SQUARE(x) x * x    // MISRA 위반: 매크로의 부작용 가능성 있음

static inline int square(int x) {
    return x * x;
}

int func1() {
    int result = SQUARE(5 + 2); // 예상치 못한 결과를 유발할 수 있음
    return result;
}

int func2() {
    int result = square(5+2);   // 안전한 결과를 제공
    return result;
}

int main() {
    int val = func2();

    return val;
}