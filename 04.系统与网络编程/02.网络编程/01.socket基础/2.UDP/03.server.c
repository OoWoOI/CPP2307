/*************************************************************************
	> File Name: 03.server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 27 Feb 2024 07:29:43 PM CST
 ************************************************************************/

#include "./common/head.h"
#define MAX_USR 512;

//使用select实现UDP的并发服务

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    } 
    
    int server, port, sockfd;
    port = atoi(argv[1]);
    
    if ((server = socket_create_udp(port)) < 0) {
        perror("soket_create_udp");
        exit(1);
    }
   
   // fd_set rfds;


    while (1) {
        
        struct sockaddr_in client;
        bzero(&client, sizeof(client));
        socklen_t len = sizeof(client);
        char buff[512] = {0};
        ssize_t rsize = recvfrom(server, buff, sizeof(buff) - 1, 0, (struct sockaddr *)&client, &len);
        if (rsize <= 0) {
            perror("recvfrom");
            continue;
        }
        char buff_send[512] = {0};
        printf("%s\n", buff);
        buff[0] = toupper(buff[0]);
        sprintf(buff_send, "%s", buff);
        sendto(server, buff_send, sizeof(buff_send) - 1, 0, (struct sockaddr *)&client, len); 
    }
    
    close(server);
    return 0;
}
