/*************************************************************************
	> File Name: chat.h
	> Author: 
	> Mail: 
	> Created Time: Tue 30 Jan 2024 09:05:50 PM CST
 ************************************************************************/

#ifndef _CHAT_H
#define _CHAT_H
struct MSG {
    char msg[1024];
    char name[20];
    pid_t server_pid;//服务端的进程号
    pthread_cond_t cond;//条件变量
    pthread_mutex_t mutex;//线程锁
};

#endif
