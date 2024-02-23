/*************************************************************************
	> File Name: 02.client.c
	> Author: 
	> Mail: 
	> Created Time: Sat 24 Feb 2024 12:24:04 AM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage : %s ip port!\n", argv[0]);
        exit(1);
    }

    int sockfd;
    if ((sockfd = socket_connect(argv[1], atoi(argv[2]))) < 0) {
        perror("socket_connect");
        exit(1);
    }

    while (1) {
        char buff[512] = {0};
        scanf("%s", buff);
        if (strlen(buff) > 0) {
            send(sockfd, buff, strlen(buff), 0);
        }
    } 
    
    return 0;
}
