/* Rule 17.3: 포인터 연산 제한
   포인터 연산은 엄격히 제한되어야 하며, 포인터 간의 덧셈, 뻴셈 등은 허용되지 않습니다.
 */

 #include <stdio.h>

int arr[3] = {1,2,3};

int func1() {
    int *p = arr;
    p = p + 1;  // MISRA 위반: 포인터 간 덧셈
    return *p;
}

int func2() {
    int *p = arr;
    p++;    // 수정: 안전하게 증가된 포인터 사용
    return *p;
}


int main() {
    int val = func2();

    return 1;
}