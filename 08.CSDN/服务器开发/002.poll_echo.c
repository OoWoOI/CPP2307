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
#include <sys/time.h>
#include <unistd.h>
#include <sys/poll.h>

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
        if (rsize == 0) return 0;
        return -1;
    }
    printf("Recv : %s\n", buff);
    return 1;
}

int send_msg(int fd, char *buff, int size) {
    int ssize = send(fd, buff, sizeof(char ) * size, 0);
    if (ssize <= 0) {
        if (ssize == 0) return 0;
        return -1;
    }
    printf("Send success!\n");
    return 1;
}

void echo_work(int server_listen) {
    struct pollfd fds[MAX_CLI + 1];
    fds[0].fd = server_listen;
    fds[0].events = POLLIN;
    int max_fd = server_listen;

    while (1) {
        int ret = poll(fds, MAX_CLI + 1, -1);
        if (ret == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        //接受连接请求
        if (fds[0].revents & POLLIN) {
            int client_fd;
            if ((client_fd = accept(server_listen, (struct sockaddr *)&clientaddr, &len)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            printf("one client connect success!\n");

            for (int i = 0; i < MAX_CLI; i++) {
                if (clients[i] == -1) {
                    clients[i] = client_fd;
                    break;
                }
            }

            //更新pollfd数组
            for (int i = 1; i  <= MAX_CLI; i++) {
                if (clients[i - 1] != -1) {
                    fds[i].fd = clients[i - 1];
                    fds[i].events = POLLIN;
                    max_fd = fds[i].fd > max_fd ? fds[i].fd : max_fd;
                }
            }
        }
        //检查客户端套接字是否有数据可读
        for (int i = 1; i <= MAX_CLI; i++) {
            if (fds[i].revents & POLLIN) {
                char buff[1024] = {0};
                if (recv_msg(fds[i].fd, buff, 1024) <= 0) {
                    printf("disconnect one client  OR error!\n");
                    close(fds[i].fd);
                    clients[i - 1] = -1;
                    continue;
                } 
                
                if (send_msg(fds[i].fd, buff, 1024) <= 0) {
                     printf("disconnect one client  OR error!\n");
                    close(fds[i].fd);
                    clients[i - 1] = -1;
                    continue;
                } 
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
    for(int i = 0; i < MAX_CLI; i++) clients[i] = -1;
    echo_work(server_listen);

    return 0;
}
