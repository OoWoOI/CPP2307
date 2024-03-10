/*************************************************************************
	> File Name: 02.udp_server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 27 Feb 2024 05:59:22 PM CST
 ************************************************************************/

#include "./common/head.h"


int main(int argc, char **argv) {
    if (argc != 2) {
        exit(1);
    }

    int listener;

    struct sockaddr_in client;

    if ((listener = socket_create_udp(atoi(argv[1]))) < 0) {
        perror("socket_create_udp");
        exit(1);
    }

    while (1) {
        udp_accept(listener, &client, atoi(argv[1]));
    }
    
    
    return 0;
}
