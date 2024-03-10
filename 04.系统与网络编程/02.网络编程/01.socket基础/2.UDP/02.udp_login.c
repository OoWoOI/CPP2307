/*************************************************************************
	> File Name: 02.udp_login.c
	> Author: 
	> Mail: 
	> Created Time: Tue 27 Feb 2024 05:59:13 PM CST
 ************************************************************************/

#include "./common/head.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage : %s ip port\n", argv[0]);
        exit(-1);
    }
    //获取传递的参数
    char ip[20] = {0};
    int port = -1;
    struct udp_login login;
    bzero(&login, sizeof(login));
    strcpy(ip, argv[1]);
    port = atoi(argv[2]);
    //设置地址空间和服务器的基本信息
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    int sockfd;
    
    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        exit(1);
    }

    login.type = UDP_SYN;//设置数据类型
    strcpy(login.msg, "hello");
    //发送第一次连接请求
    sendto(sockfd, &login, sizeof(login), 0, (struct sockaddr *)&server, sizeof(server));
    //等待第一次请求的回应
    recvfrom(sockfd, &login, sizeof(login), 0, NULL, NULL);
    printf("login.msg = %s\n", login.msg);
    //获取连接
    int ret = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    strcpy(login.msg, "ACK for login!");
    ret = send(sockfd, &login, sizeof(login), 0);
    printf("ret = <%d>\n", ret);
    perror("ret");
    return 0;
}

