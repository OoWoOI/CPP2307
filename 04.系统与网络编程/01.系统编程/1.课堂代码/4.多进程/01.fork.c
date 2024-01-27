/*************************************************************************
	> File Name: 01.fork.c
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jan 2024 08:19:20 PM CST
 ************************************************************************/

#include "./common/head.h"
int main() {
    printf("Hello word !");
    
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        printf("I'm a child !\n");
    } else {
        printf("I'm a parent !\n");
    }

    
    return 0;
}
