/*************************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Jan 2024 09:11:14 PM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

//事件级别
#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_ERROR 2

void log_event(int level, const char *message, const char *filename);
int make_block(int fd);
int make_nonblock(int fd);
semaphore make_semaphore(int value);
void P(semaphore sem);
void V(semaphore sem);

#endif
