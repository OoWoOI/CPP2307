/*************************************************************************
	> File Name: 1.send_file.c
	> Author: 
	> Mail: 
	> Created Time: Wed 28 Feb 2024 10:02:13 AM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage : %s ip port file!\n", argv[0]);
        exit(1);
    } 

    int sockfd = socket_connect(argv[1], atoi(argv[2]));
    if (sockfd < 0) {
        perror("socket_connect");
        exit(1);
    }

    send_file(sockfd, argv[3]);
    DBG("hello\n");

    return 0;
}
