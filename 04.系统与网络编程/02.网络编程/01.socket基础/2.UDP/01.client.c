/*************************************************************************
	> File Name: 01.client.c
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Feb 2024 11:29:10 PM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage : %s ip port!", argv[0]);
        exit(1);
    }
    
    char ip[20] = {0};
    int port = -1, sockfd;
    strcpy(ip, argv[1]);
    port = atoi(argv[2]);
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(ip);
    client.sin_port = htons(port);
    if ((sockfd = socket_udp()) < 0) {
        perror("sockfd_udp");
        exit(1);
    }
    while (1) {
        char buff[512] = {0};
        scanf("%s", buff);
        if (!strlen(buff)) continue;
        sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&client, sizeof(client));
    }
    return 0;
}
