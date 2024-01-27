/*************************************************************************
	> File Name: 03.git.c
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jan 2024 09:57:24 PM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    int opt, flag  = 0;
    char message[1024] = {0};
    while ((opt = getopt(argc, argv, "m:")) != -1) {
        switch (opt) {
            case 'm': {
                strcpy(message, optarg);
                printf("%s\n", message);
                return 0;
            }
            default: {
                break;
            }
        }
    }
    //默认情况下处理: 打开一个vim编辑器，输入一个message信息
    pid_t pid_vim, pid_cat, pid_rm;
    if ((pid_vim = fork()) < 0) {
        perror("fork()");
        exit(1);
    } 

    if (pid_vim == 0) {
        execlp("vim", "vim", "data.txt", NULL);
    } 
    
    wait(NULL);

    if ((pid_cat = fork()) < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid_cat == 0){
        execlp("cat", "cat", "data.txt", NULL);
    }

    wait(NULL);

    if ((pid_rm = fork()) < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid_rm == 0) {
        execlp("rm", "rm", "./data.txt", NULL);
    }
    wait(NULL);
    return 0;
}
