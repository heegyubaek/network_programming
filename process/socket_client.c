#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = "Hello, Server!";

    // 소켓 생성
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 서버에 연결
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 메시지 전송 및 수신
    send(sock, buffer, strlen(buffer), 0);
    int len = read(sock, buffer, sizeof(buffer));
    buffer[len] = '\0';
    printf("Received from server: %s\n", buffer);

    // 소켓 종료
    close(sock);

    return 0;
}
