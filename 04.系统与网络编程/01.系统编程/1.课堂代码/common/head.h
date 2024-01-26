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

//user's head file
#include "color.h"
#include "common.h"


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
