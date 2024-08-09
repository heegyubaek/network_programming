/* Rule 18.1 : 표준 헤더 파일 사용
    표준 라이브러리의 헤더 파일은 변경 없이 사용해야 함
 */

 #include <stddef.h>    //수정: 표준 헤더 파일 사용

 #define MY_NULL ((void *)0)    // MISRA 위한: 표준 헤더의 매크로를 재정의

void func1() {
    int *p = MY_NULL;
}

void func2() {
    int *p = NULL; //표준 정의된 NULL 사용
}

int main() {
    func2();

    return 1;
}