/*************************************************************************
	> File Name: 04.check_argv0_of_execl.c
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jan 2024 10:37:53 PM CST
 ************************************************************************/

#include "./common/head.h"

int main() {
    
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) {
        execl("./a.out", "myargv", NULL);
    }

    wait(NULL);
    
    return 0;
}

