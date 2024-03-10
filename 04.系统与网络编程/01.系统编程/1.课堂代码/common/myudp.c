/*************************************************************************
	> File Name: myudp.c
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Feb 2024 11:04:29 PM CST
 ************************************************************************/

#include "head.h"

int socket_create_udp(int port) {
    int listener;
    if ((listener = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);
    int reuse = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &reuse, (socklen_t)sizeof(reuse));
    if (bind(listener, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind");
        return -1;
    }
    return listener;
}

int socket_udp() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
       return -1; 
    }
    return sockfd;
}

int udp_connect(struct sockaddr_in *addr, int loc_port) {
    int sockfd;
    
    if ((sockfd = socket_create_udp(loc_port)) < 0) {
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) {
        return -1;
    }

    
    return sockfd;
}


int udp_accept(int sockfd, struct sockaddr_in *addr, int loc_port) {
    int newfd;
    struct udp_login login;
    bzero(&login, sizeof(login));
    socklen_t len = sizeof(struct sockaddr );
    //① 第一次接收请求连接的信息
    ssize_t rsize = recvfrom(sockfd, &login, sizeof(login), 0, (struct sockaddr *)addr, &len);
    if (rsize != sizeof(login)) {
        return -1;
    }
    //判断收到的信息受否为SYN
    if (login.type & UDP_SYN) {
        DBG("Client %s : %d want to login : <%s>\n", inet_ntoa(addr->sin_addr), addr->sin_port, login.msg);
        //发送第二次握手
        login.type |= UDP_ACK;//*
        bzero(login.msg, sizeof(login.msg));
        strcpy(login.msg, "SYN recived!");
        //②确认收到请求，并返回确认信息
        sendto(sockfd, &login, sizeof(login), 0, (struct sockaddr *)addr, len);
    } else {
        //出现问题,未接受到请求连接的信息
        DBG("Error in udp packet, Not UDP_SYN!\n");
        return -1;
    }

    if ((newfd = udp_connect(addr, loc_port)) < 0) {
        return -1;
    }

    DBG("newfd got a %d !\n", newfd);

    //成功建立连接
    recv(newfd, &login, sizeof(login), 0);

    DBG("newfd -> %s\n", login.msg);
    

    return newfd;
}
