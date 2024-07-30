#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(client_addr);

    // 소켓 생성
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // 바인드 및 리스닝
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 3);

    printf("Server is waiting for a connection...\n");

    // 클라이언트 연결 수락
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    printf("Connection established!\n");

    // 메시지 수신 및 에코
    int len = read(client_fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    write(client_fd, buffer, len);

    // 소켓 종료
    close(client_fd);
    close(server_fd);

    return 0;
}
