/*
 * client.cpp
 *
 *  Created on: Jul 15, 2017
 *      Author: baekhg
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>

#define MAXBUF  256

int main(int argc, char **argv)
{
    struct sockaddr_in clientaddr;
    int client_sockfd;
    int client_len;
    char buf[MAXBUF];
    char rbuf[MAXBUF];

    if((client_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("error : ");
        exit(0);
    }

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientaddr.sin_port = htons(atoi(argv[1]));

    client_len = sizeof(clientaddr);

    if(connect(client_sockfd, (struct sockaddr *)&clientaddr, client_len) < 0)
    {
        perror("connect error : ");
        exit(0);
    }

    while(1)
    {
        memset(buf, 0x00, MAXBUF);

        printf("Client : ");
        fgets(buf, 1024, stdin);

        buf[strlen(buf) - 1] = '\0';

        if(write(client_sockfd, buf, MAXBUF) <= 0)
        {
            perror("write error : ");
            break;
        }
        memset(buf, 0x00, MAXBUF);
        if(read(client_sockfd, buf, MAXBUF) <= 0)
        {
            perror("read error : ");
            break;
        }
        printf("read : %s \n", buf);
    }

    close(client_sockfd);

    return 0;
}

