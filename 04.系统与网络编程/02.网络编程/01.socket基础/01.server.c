/*************************************************************************
	> File Name: 01.server.c
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Feb 2024 11:36:56 PM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    int server_listen, port = 0;
    if (argc != 2) {
        fprintf(stderr, "Usage %s -p port!\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);
    printf("%d\n", port);
    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_port");
        exit(1);
    }

   //建立连接
    int new_fd;
    if ((new_fd = accept(server_listen, NULL, NULL)) < 0) {
        perror("accept");
        exit(1);
    }
   
    while (1) {
        char buff[1024] = {0};
        recv(new_fd, buff, 1023, 0);
        printf("%s\n", buff);
        fflush(stdout);
    }
    sleep(10);

    return 0;
}
