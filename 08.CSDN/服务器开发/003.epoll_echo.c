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
#include <sys/epoll.h>

#define MAX_CLI 50

int clients[MAX_CLI];
struct sockaddr_in clientaddr;
socklen_t len = sizeof(clientaddr);


void print_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

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
    int epollfd  = epoll_create(1);//创建epoll实例
    if (epollfd < 0)  
        print_error("epoll_create");
    
    struct epoll_event event, events[MAX_CLI];
    event.events = EPOLLIN;
    event.data.fd = server_listen;//将server_listen添加到epoll实例中
    
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, server_listen, &event) < 0) 
        print_error("epoll_ctl");
    
    while (1) {
        int num_events = epoll_wait(epollfd, events, MAX_CLI, -1);//等待事件发生
        
        if (num_events < 0) 
            print_error("epoll_wait");

        for (int i = 0; i < num_events; i++) {
            if (events[i].data.fd == server_listen) {
                int cli_fd = accept(server_listen, (struct sockaddr*)&clientaddr, &len);
                if (cli_fd < 0) 
                    print_error("accept");
                printf("new connection success\n");

                //将客户端添加到epoll实例中去
                event.events = EPOLLIN;
                event.data.fd = cli_fd;

                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, cli_fd, &event) < 0) 
                    perror("epoll_ctl");

            } else {
                //接收消息，回复消息
                int cli_fd = events[i].data.fd;
                char buff[1024] = {0};
                int ret;

                if ((ret = recv_msg(cli_fd, buff, 1024)) <= 0) {
                    ret == 0 ? printf("连接中断\n") : printf("客户端异常\n");
                    if (epoll_ctl(epollfd, EPOLL_CTL_DEL, cli_fd, NULL) < 0) 
                        print_error("epoll_ctl");
                    close(cli_fd);
                    continue;
                }
                    
                    send_msg(cli_fd, buff, strlen(buff));//回显数据
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
