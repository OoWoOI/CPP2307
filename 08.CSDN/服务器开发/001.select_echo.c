/*************************************************************************
	> File Name: 001.select_echo.c
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Apr 2024 07:47:11 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>


#define MAX_CLI 50

int clients[MAX_CLI];
struct sockaddr_in clientaddr;
socklen_t len = sizeof(clientaddr);

int socket_create(int port) {//创建并绑定网络监听的socket套接字
    int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(fd, 20) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    return fd;
}
int recv_msg(int fd, char *buff, int size) { 

    int rsize = recv(fd, buff, sizeof(char ) * size, 0);
    if (rsize <= 0) {
        return -1;
    }
    printf("Recv : %s\n", buff);
    return 0;
}

int send_msg(int fd, char *buff, int size) {
    int ssize = send(fd, buff, sizeof(char ) * size, 0);
    if (ssize <= 0) {
        return -1;
    }
    printf("Send success!\n");
    return 0;
}

void echo_work(int server_listen) {
    for (int i = 0; i < MAX_CLI; i++) clients[i] = -1;//初始化数组
    while (1) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(server_listen, &rfds);
        int max_fd = server_listen;

        for (int i = 0; i < MAX_CLI; i++) {
            int fd = clients[i];
            if (fd != -1) {
                FD_SET(fd, &rfds);
                max_fd = fd > max_fd ? fd : max_fd;
            }
        }

        int ret = select(max_fd + 1, &rfds, NULL, NULL, NULL);
        if (ret < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }
        if (FD_ISSET(server_listen, &rfds)) {
            int clientfd;
            if((clientfd = accept(server_listen, (struct sockaddr *)&clientaddr, &len)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            printf("one client accpet succes\n");
            for (int i = 0; i < MAX_CLI; i++) {
                if (clients[i] == -1) {
                    clients[i] = clientfd;
                    break;
                }
            } 
        }

        for (int i = 0; i < MAX_CLI; i++) {
            int fd = clients[i];
            if (fd != -1 && FD_ISSET(fd, &rfds)) {
                char buff[1024] = {0};
                if (recv_msg(fd, buff, 1024) < 0) {
                    clients[i] = -1;
                    close(fd);
                }//接收数据

                if (send_msg(fd, buff, 1024) < 0) {
                    clients[i] = -1;
                    close(fd);
                }//回显数据
            }
        }
    }
    
    return ;
}


int main() {
    int server_listen;

    if ((server_listen = socket_create(8080)) < 0) {
        perror("socket_create");
        exit(EXIT_FAILURE);
    }
    
    echo_work(server_listen);

    return 0;
}
