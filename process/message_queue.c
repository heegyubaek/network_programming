#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX 100

// 메시지 버퍼 정의
struct mesg_buffer {
    long mesg_type;
    char mesg_text[MAX];
} message;

int main() {
    key_t key;
    int msgid;

    // 키 생성
    key = ftok("progfile", 65);

    // 메시지 큐 생성
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;

    printf("Write Message : ");
    fgets(message.mesg_text, MAX, stdin);

    // 메시지 전송
    msgsnd(msgid, &message, sizeof(message), 0);

    printf("Data sent is : %s \n", message.mesg_text);

    return 0;
}
