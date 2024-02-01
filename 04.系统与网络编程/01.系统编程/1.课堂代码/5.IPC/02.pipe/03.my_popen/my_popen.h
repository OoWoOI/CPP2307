/*************************************************************************
	> File Name: my_popen.h
	> Author: 
	> Mail: 
	> Created Time: Thu 01 Feb 2024 04:38:12 PM CST
 ************************************************************************/

#ifndef _MY_POPEN_H
#define _MY_POPEN_H
FILE *my_popen(const char *cmd, const char *type);
int my_pclose(FILE *fp);
#endif
