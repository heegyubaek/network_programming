#include <stdio.h>
#include <signal.h>
#include <unistd.h>

char flag = 1;

// 시그널 핸들러 함수
void handle_sigint(int sig) {
    printf("Caught signal %d\n", sig);
    // 종료 작업 등을 여기서 수행 가능
		flag = 0;
}

int main() {
    // 시그널 핸들러 설정
    signal(SIGINT, handle_sigint);

    printf("Running... Press Ctrl+C to exit.\n");

    // 무한 루프
    while (flag) {
        sleep(1); // 잠깐 대기
    }

    return 0;
}
