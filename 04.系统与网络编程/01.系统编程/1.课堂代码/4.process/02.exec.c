/*************************************************************************
	> File Name: 02.exec.c
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jan 2024 09:42:38 PM CST
 ************************************************************************/

#include  "./common/head.h"
int main() {
    pid_t pid;
    
    int wstatus;

    if ((pid = fork()) < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) {
        //子进程实现ping命令
        execlp("vim", "vim", "data.txt", NULL);
        printf("I'm a child !\n");
    }
    
    wait(&wstatus);

    printf("The Return Value of child is %d\n", WEXITSTATUS(wstatus));

    return 0;
}
