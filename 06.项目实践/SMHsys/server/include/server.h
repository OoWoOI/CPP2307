/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: Tue 07 May 2024 10:38:47 PM CST
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

typedef struct ServerInfo {
    char *IP,
    int PORT,
    int CLIENT_MAX_NUM,//CLIENT_MAX_NUM
    char *LOG_PATH,
    char *CONF_PATH
} ServerInfo;


extern ServerInfo *sv;


int server_run();

#endif
