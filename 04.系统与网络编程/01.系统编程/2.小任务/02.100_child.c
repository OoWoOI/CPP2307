/*************************************************************************
	> File Name: 02.100_child.c
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jan 2024 08:21:12 PM CST
 ************************************************************************/

#include "./common/head.h"
int main() {
    //ToDo: 使用fork创建100个子进程，并打印出他们的序号和进程号
    
    pid_t pid;

    for (int i  = 0; i < 100; i++) {
        if ( (pid = fork()) < 0) {
            perror("fork()");
            exit(1);
        }
        if (pid == 0) {
            printf("I'm a child pid = %d, num = %d\n", getpid(), i + 1);
            return 0;
        }
        wait(NULL);
    }
    
    return 0;
}
