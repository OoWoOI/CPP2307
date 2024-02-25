/*************************************************************************
	> File Name: 04.server.c
	> Author: 
	> Mail: 
	> Created Time: Sat 24 Feb 2024 03:39:22 PM CST
 ************************************************************************/

#include "./common/head.h"
//基于select实现的并发服务器

#define MAXUSER 512

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }

    int server_listen, port = 0;
    port = atoi(argv[1]);
    int fd[MAXUSER] = {0};
    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create");
        exit(1);
    }  
    
    fd_set readfds;
    fd[server_listen] = server_listen;
    int maxfd = server_listen;//设置server_listen为最大的文件描述符
    int sockfd;
    while (1) {
        //reinit
        FD_ZERO(&readfds);
        for (int i = 3; i <= maxfd; i++) {
            if (fd[i]) {
                FD_SET(fd[i], &readfds);
            }
        }//将已存在的文件描述符加入到监控集合中
        
        int ret = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (FD_ISSET(server_listen, &readfds)) {//当server_listen存在于监控集合中时
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            bzero(&client, len);
            if ((sockfd = accept(server_listen, (struct sockaddr *)&client, &len)) < 0) {
                perror("accept");
                exit(1);
            }
            printf("%s : <%d> login !\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            if (sockfd >= MAXUSER - 5) {
                fprintf(stderr, "Too many usrs !\n");
                close(sockfd);
            } else {
                fd[sockfd] = sockfd;
                if (sockfd > maxfd) maxfd = sockfd;
            }
        }
        
        //输出信息
        for (int i = 3; i <= maxfd; i++) {
            if (fd[i] == 0) continue;
            if (fd[i] == server_listen) continue;
            if (FD_ISSET(fd[i], &readfds)) {
                printf("%d is ready !\n", fd[i]);
                char buff[512] = {0};
                size_t rsize = recv(fd[i], buff, sizeof(buff) - 1, 0);
                if (rsize <= 0) {//连接中断或其他异常
                    perror("recv");
                    close(fd[i]);
                    fd[i] = 0;
                    continue;
                }
                printf("%s\n", buff);
                send(fd[i], buff, rsize, 0);//回显数据
            }
        }
    }
    

    return 0;
}


