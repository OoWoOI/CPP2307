/*************************************************************************
	> File Name: tcp.c
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Feb 2024 10:45:26 PM CST
 ************************************************************************/

#include "head.h"

int socket_create(int port) {
    int server_listen;
    if ((server_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }//创建socket套接字
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("0.0.0.0");
    int reuse_val = 1;
    setsockopt(server_listen, SOL_SOCKET, SO_REUSEADDR, (void *)&reuse_val, sizeof(int));

    if (bind(server_listen, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }//绑定ip地址及端口
    
    if (listen(server_listen, 20) < 0) {
        return -1;
    }//监听socket套接字
    return server_listen;
}

int socket_connect(const char *ip, const int port) {
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }//获取一个套接字

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }//获取连接
    
    return sockfd;
}

//具有定时的网络连接
int socket_connect_timeout(const char *ip, const int port, long timeout) {
    int sockfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    //将sockfd转换为非阻塞
    make_nonblock(sockfd);
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec= timeout;
    
    fd_set wfds;
    FD_ZERO(&wfds);
    FD_SET(sockfd, &wfds);
    //获取连接：当出现连接失败后，直接开始倒计时;
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        int err = -1;
        int len = sizeof(int);
        int ret = select(sockfd + 1, NULL, &wfds, NULL, &tv);
        if (ret <= 0) {
            close(sockfd);
            return -1;
        } else if (ret) {
            if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &err, (socklen_t *)&len) < 0) {
                close(sockfd);
                return -1;
            } 
                
            if (err) {
                close(sockfd);
                return -1;
            }
        } 

    }
    //将sockfd还原
    make_block(sockfd);
    return sockfd;
}
