#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>

#define MAXBUF 256

int main(int argc, char **argv)
{
    int server_sockfd, client_sockfd;
    unsigned int client_len, n;
    char buf[MAXBUF];
    struct sockaddr_in clientaddr, serveraddr;

    client_len = sizeof(clientaddr);

    //Create socket
    if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error : ");
        exit(0);
    }

    //Binding socket
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(atoi(argv[1]));
    bind(server_sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    //Listen socket
    listen(server_sockfd, 5);

    while(1)
    {
        memset(buf, 0x00, MAXBUF);
        //Accept socket
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr, &client_len);

        while(1)
        {
            if((n = read(client_sockfd, buf, MAXBUF)) < 0)
            {
                close(client_sockfd);
                break;
            }
            printf("read : %s \n", buf);
            if(write(client_sockfd, buf, MAXBUF) < 0)
            {
                perror("write error : ");
                close(client_sockfd);
                break;
            }
        }
        close(client_sockfd);
    }


    return -1;
}
