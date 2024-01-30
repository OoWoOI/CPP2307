/*************************************************************************
	> File Name: 01.base_on_file.c
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jan 2024 11:36:13 PM CST
 ************************************************************************/

#include "./common/head.h"
int main() {
    pid_t pid;
    FILE *fp = fopen("./letter", "rw");
    if (fp == NULL) {
        fprintf(stderr, "create file error !\n");
        exit(1);
    }
    
    if ((pid = fork()) < 0) {
        perror("fork()");
        exit(1);
    }
    
    if (pid == 0) {
        //子进程读数据:fread()
        sleep(1);
        char buff[1024] = {0};
        int ret = fread(buff, 100, 10, fp);
        printf("ret = %d\n%s", ret, buff);
    } else {
        //父进程写数据:fwrite()
        fwrite("hello I'm a letter\n", 10, 2, fp);
    }
   
    return 0;
}
