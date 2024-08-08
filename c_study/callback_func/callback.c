#include <stdio.h>

// 작업을 정의하는 함수들
void printElement(int element) {
    printf("Element: %d\n", element);
}

void doubleElement(int element) {
    printf("Double: %d\n", element * 2);
}

// 콜백 함수를 받는 함수
void processArray(int *array, int size, void (*callback)(int)) {
    for (int i = 0; i < size; i++) {
        callback(array[i]);  // 콜백 함수 호출
    }
}

int main() {
    int myArray[] = {1, 2, 3, 4, 5};
    int size = sizeof(myArray) / sizeof(myArray[0]);

    printf("Printing elements:\n");
    processArray(myArray, size, printElement);

    printf("\nDoubling elements:\n");
    processArray(myArray, size, doubleElement);

    return 0;
}
