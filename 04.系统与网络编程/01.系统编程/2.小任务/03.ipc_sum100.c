/*************************************************************************
	> File Name: 03.ipc_sum100.c
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Jan 2024 05:20:46 AM CST
 ************************************************************************/

#include "./common/head.h"

//ToDo: 计算1 - 100的累加和
//要求: (1) 必须使用fork、open、flock

void showsum(int cnt); //打印计算机结果
int getSum(int fd);//获取计算结果
void setSum(int fd, int sum);//更新计算结果
int getFD();//获取一个文件描述符

int main(int argc, char **argv) {
    int opt, cnt;
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                cnt = atoi(optarg);
                showsum(cnt);
                break;
            default :
                fprintf(stderr, "Usage : %s is -n cnt!", argv[0]);
                exit(1);
        }
    }
    return 0;
}

void showsum(int cnt) {
    
    pid_t pid;
    static int sum = 0;
    int fd = getFD();

    for (int i = 0; i < cnt; i++) {
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(1);
        }
        
        if (pid == 0) {
            //子进程处理数据加和
            if (flock(fd, LOCK_EX) < 0) {
                perror("flock LOCK_EX");
                exit(1);
            }
            
            int sum = getSum(fd) + 1;
            printf("pid = %d, sum = %d\n", getpid(), sum);
            if (sum > 100) {
                flock(fd, LOCK_UN);
                exit(EXIT_SUCCESS) ;
            }
            
            if (flock(fd, LOCK_UN) < 0) {
                perror("flock LOCK_UN");
                exit(1);
            }
            close(fd);
            exit(EXIT_SUCCESS);
        } 
    }

    for (int i = 0; i < cnt; i++) wait(NULL);//等待所以子进程都结束
    
    //父进程打印累加和
    printf("sum = %d\n", getSum(fd));
    close(fd);
    return ;
}

int getFD() {
    int fd = open("./tmp.txt", O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    return fd;
}

int getSum(int fd) {
    lseek(fd, 0, SEEK_SET);
    int sum;
    read(fd, &sum, sizeof(int));
    return sum;
}

void setSum(int fd, int sum) {
    lseek(fd, 0, SEEK_SET);
    write(fd, &sum, sizeof(int));
    return ;
}
