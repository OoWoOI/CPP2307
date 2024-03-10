/*************************************************************************
	> File Name: 1.recv_server.c
	> Author: 
	> Mail: 
	> Created Time: Wed 28 Feb 2024 10:08:54 AM CST
 ************************************************************************/

#include "./common/head.h"

int main(int argc, char **argv) {
    
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port !\n", argv[0]);
        exit(1);
    }

    int server_listen, sockfd = 0;
    
    if ((server_listen = socket_create(atoi(argv[1]))) < 0) {
        perror("socket_create");
        exit(1);
    }

    while (1) {
        if ((sockfd = accept(server_listen, NULL, NULL)) < 0) {
            perror("accept");
            exit(1);
        }
        pid_t pid;
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            recv_file(sockfd);
            close(sockfd);
            break;
        }
        wait(NULL);
        close(sockfd);
    }
    
    return 0;
}

