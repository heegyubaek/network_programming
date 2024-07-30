#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello, child process!";
    char read_msg[100];

    // 파이프 생성
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // 자식 프로세스 생성
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) { // 부모 프로세스
        close(fd[0]); // 읽기 끝을 닫음
        write(fd[1], write_msg, strlen(write_msg) + 1); // 메시지 쓰기
        close(fd[1]); // 쓰기 끝을 닫음
    } else { // 자식 프로세스
        close(fd[1]); // 쓰기 끝을 닫음
        read(fd[0], read_msg, sizeof(read_msg)); // 메시지 읽기
        printf("Received message: %s\n", read_msg);
        close(fd[0]); // 읽기 끝을 닫음
    }

    return 0;
}
