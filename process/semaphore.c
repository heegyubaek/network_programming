#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void* process(void* arg) {
    int id = *(int*)arg;

    printf("Process %d waiting to enter critical section...\n", id);
    sem_wait(&semaphore); // 세마포어를 기다림
    printf("Process %d entered critical section\n", id);

    // 임계 구역 (critical section)
    sleep(2); // 임계 구역에서 2초 대기

    printf("Process %d leaving critical section\n", id);
    sem_post(&semaphore); // 세마포어 해제

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // 세마포어 초기화, 초기 값은 1
    sem_init(&semaphore, 0, 1);

    // 두 개의 스레드를 생성하여 프로세스 흉내
    pthread_create(&t1, NULL, process, &id1);
    pthread_create(&t2, NULL, process, &id2);

    // 스레드가 종료될 때까지 기다림
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // 세마포어 제거
    sem_destroy(&semaphore);

    return 0;
}
