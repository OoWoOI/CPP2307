/*************************************************************************
	> File Name: file.h
	> Author: 
	> Mail: 
	> Created Time: Wed 28 Feb 2024 09:08:33 AM CST
 ************************************************************************/

#ifndef _FILE_H
#define _FILE

struct file_msg {
    char name[50];
    char buff[4096];
    long size;
    int msgsize;
};

int send_file(int sockfd, char *filename);//发送文件
int recv_file(int sockfd);//接收文件

#endif
