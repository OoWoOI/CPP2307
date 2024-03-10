/*************************************************************************
	> File Name: 03.client.c
	> Author: 
	> Mail: 
	> Created Time: Tue 27 Feb 2024 07:51:56 PM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage : %s ip port !\n", argv[0]);
        exit(1);
    }
    //服务器地址信息
    struct sockaddr_in server;
    int sockfd, port;
    port = atoi(argv[2]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(port);
    
    //获取套接字
    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        exit(1);
    }


    struct sockaddr client;
    socklen_t len = sizeof(client);
    while (1) {
        char buff[512] = {0};
        scanf("%s", buff);
        sendto(sockfd, buff, sizeof(buff) - 1, 0, (struct sockaddr *)&server, sizeof(server));
        bzero(buff, sizeof(buff));//清空
        int ret = recvfrom(sockfd, buff, sizeof(buff) - 1, 0, &client, &len);
        if (ret <= 0) {
            perror("recvfrom");
            break;
        }
        printf("%s\n", buff);
    }
    
    
    
    return 0;
}
