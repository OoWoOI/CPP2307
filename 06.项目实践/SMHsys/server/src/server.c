/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 07 May 2024 10:35:36 PM CST
 ************************************************************************/

#include<stdio.h>
#include<server.h>
#include<utils.h>
#include<conf.h>


__attribute__((constructor()))
void init_server() {
    DBG(GREEN"Init server\n"NONE);
    
    return ;
}

int server_run() {
    DBG(RED"Server Run\n"NONE);
    return 0;
}

