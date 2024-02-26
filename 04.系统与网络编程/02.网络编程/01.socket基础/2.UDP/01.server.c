/*************************************************************************
	> File Name: 01.server.c
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Feb 2024 11:28:57 PM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port !\n", argv[0]);
        exit(1);
    }
    int server, port;
    port = atoi(argv[1]);
    if ((server = socket_create_udp(port)) < 0) {
        perror("socket_create_udp");
        exit(1);
    }
    
    while (1) {
        char buff[512] = {0};
        ssize_t rsize = recvfrom(server, buff, sizeof(buff) - 1, 0, NULL, NULL);
        if (rsize <= 0) {
            perror("recvfrom");
            exit(1);
        }
        printf("%s\n", buff);
    }



    return 0;
}
