/*************************************************************************
	> File Name: 02.server.c
	> Author: 
	> Mail: 
	> Created Time: Sat 24 Feb 2024 01:24:28 PM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }

    int server_listen = 0, sockfd = 0, port = atoi(argv[1]);
    
    if ((server_listen = socket_create(port)) <= 0) {
        perror("socket_create");
        exit(1);
    }

    while (1) {//服务端持续监听连接
        struct sockaddr_in client;
        memset(&client, 0, sizeof(client));
        socklen_t len = sizeof(client);
        if ((sockfd = accept(server_listen, (struct sockaddr *)&client, &len)) < 0) {
            perror("accept");
            exit(1);
        }
        printf("<%s, %d> client connect in !\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        //创建子进程实现多进程并发服务器
        pid_t pid;
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) break;
        close(sockfd);//关闭连接
    }
    //子进程实现持续发送
    while (1) {
        char buff[512] = {0};
        ssize_t ret = recv(sockfd, buff, 511, 0);
        if (ret <= 0) {
            perror("recv");
            close(sockfd);//关闭连接;
            exit(1);
        }
        printf("%s\n", buff);
    }
    
    return 0;
}
