#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = 1234;
    int shmid;
    char *data;

    // 공유 메모리 생성
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // 공유 메모리에 접근
    data = (char*) shmat(shmid, (void*)0, 0);

    printf("Write Data : ");
    fgets(data, 1024, stdin);

    printf("Data written in memory: %s\n", data);

    // 공유 메모리에서 분리
    shmdt(data);

    return 0;
}
