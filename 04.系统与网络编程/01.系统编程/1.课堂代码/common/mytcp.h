/*************************************************************************
	> File Name: mytcp.h
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Feb 2024 11:40:35 PM CST
 ************************************************************************/

#ifndef _MYTCP_H
#define _MYTCP_H
int socket_create(int port);
int socket_connect(const char *ip, const int port);
int socket_connect_timeout(const char *ip, const int port, long timeout);
#endif
