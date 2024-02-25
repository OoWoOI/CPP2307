/*************************************************************************
	> File Name: 03.server.c
	> Author: 
	> Mail: 
	> Created Time: Sat 24 Feb 2024 03:02:58 PM CST
 ************************************************************************/

#include "../common/head.h"

void *worker(void *arg) {
    int fd = *(int *)arg;

    while (1) {
        char buff[512] = {0};
        ssize_t ret = recv(fd, buff, 511, 0);
        if (ret <= 0) {
            perror("recv");
            close(fd);
            break;
        }
        printf("%s\n", buff);
        send(fd, buff, 511, 0);
    }
    
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port !\n", argv[0]);
        exit(1);
    }

    int server_listen, sockfd, port = 0;
    port = atoi(argv[1]);

    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create");
        exit(1);
    }
    
    while (1) {
        struct sockaddr_in client;
        memset(&client, 0, sizeof(client));
        socklen_t len = sizeof(client);
        if ((sockfd = accept(server_listen, (struct sockaddr *)&client, &len)) < 0) {
            perror("accept");
            exit(1);
        }
        pthread_t *tid = calloc(sizeof(pthread_t), 1);

        pthread_create(tid, NULL, worker, (void *)&sockfd);
    }
    
    return 0;
}
