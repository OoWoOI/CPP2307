/*************************************************************************
	> File Name: head.h
	> Author: 
	> Mail: 
	> Created Time: Thu 22 Feb 2024 04:14:35 PM CST
 ************************************************************************/
/*************************************************************************
	> File Name: head.h
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2024 06:58:28 PM CST
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H
// sys's head file
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  
#include <netinet/udp.h>
#include <ctype.h>

//user's head file
#include "color.h"
#include "common.h"
#include "mytcp.h"
#include "threadpool.h"
#include "myudp.h"
#include "file.h"

//测试宏
#ifdef _D
#define DBG(formt, arg...) {\
    printf("[ %s : %s : %d ] ", __FILE__, __func__, __LINE__);\
    printf(formt, ##arg);\
}
#else
#define DBG(formt, arg...)
#endif

#endif
