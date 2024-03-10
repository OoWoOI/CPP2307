/*************************************************************************
	> File Name: myudp.h
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Feb 2024 11:03:39 PM CST
 ************************************************************************/

#ifndef _MYUDP_H
#define _MYUDP_H

#define UDP_SYN 0x01
#define UDP_ACK 0x02
#define UDP_FIN 0x04


struct udp_login {
    int port;//能够反向连接回去，prot是必须的吗?
    int type;//tcp三次握手
    char msg[512];
};

int socket_create_udp(int port);
int socket_udp();
int udp_accept(int sockfd, struct sockaddr_in *addr, int loc_port);
int udp_connect(struct sockaddr_in *addr, int loc_port);

#endif
