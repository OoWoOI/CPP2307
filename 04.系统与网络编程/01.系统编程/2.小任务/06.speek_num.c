/*************************************************************************
	> File Name: 06.speek_num.c
	> Author: 
	> Mail: 
	> Created Time: Mon 29 Jan 2024 12:57:23 AM CST
 ************************************************************************/

#include "./common/head.h"

//ToDo: 使用多进程、open、fork、flock实现报数 1 - 100;
#define PATHNAME "./num.txt"

void do_work(int cnt);//报数
int getNum(int fd);//获取数字
void setNum(int fd, int num);//设置数字

int main(int argc, char **argv) {
    int opt, cnt;

    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                cnt = atoi(optarg);
                do_work(cnt);
                break;
            default :
                fprintf(stderr, "Usage : %s is -n cnt !\n", argv[0]);
                exit(1);
        }
    }
    
    return 0;
}

void do_work(int cnt) {
    pid_t pid = 0;
    int fd; 
    for (int i = 0; i < cnt; i++) { 
        if ((pid = fork()) < 0) {
            perror("fork()");
            exit(1);
        }

        if (pid == 0) {
            //子进程实现报数
            fd = open(PATHNAME, O_CREAT | O_RDWR, 0644);
            flock(fd, LOCK_EX);
            int num = getNum(fd) + 1;
            setNum(fd, num);
            flock(fd, LOCK_UN);
            if (num > 100) {
                close(fd);
                exit(0);
            }
            printf("num = %d， pid = %d\n", num, getpid());
            close(fd);
        }
    }
    
    for (int i = 0; i < cnt; i++) wait(NULL);
    close(fd);
    return ;
}

int getNum(int fd) {
  //  lseek(fd, 0, SEEK_SET);
    int num = 0;
    pread(fd, &num, sizeof(int), 0);
    return num;
}

void setNum(int fd, int num) {
   // lseek(fd, 0, SEEK_SET);
    pwrite(fd, &num, sizeof(int), 0);
    return ;
}
