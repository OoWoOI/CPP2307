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
int getNum(int fd);//获取计算结果
void setNum(int fd, int sum);//更新计算结果
int getFD(const char *pathname);//获取一个文件描述符

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
    int fd_sum = getFD("./sum.txt");
    int fd_num = getFD("./num.txt");

    for (int i = 0; i < cnt; i++) {
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(1);
        }
        
        if (pid == 0) {
            //子进程处理数据加和
            if (flock(fd_sum, LOCK_EX) < 0) {
                perror("flock LOCK_EX fd_sum");
                exit(EXIT_FAILURE);
            }

            if (flock(fd_num, LOCK_EX) < 0) {
                perror("flock LOCK_EX fd_num");
                exit(EXIT_FAILURE);
            }
            
            int sum = getNum(fd_sum);
            int num = getNum(fd_num);
        
            if (num >= 100) {
                flock(fd_num, LOCK_UN);
                flock(fd_sum, LOCK_UN);
                exit(EXIT_SUCCESS) ;
            } 
            
            sum += (num + 1);
            num++;

            setNum(fd_sum, sum);
            setNum(fd_num, num);
            
            if (flock(fd_sum, LOCK_UN) < 0) {
                perror("flock LOCK_UN");
                exit(EXIT_FAILURE);
            }

            if (flock(fd_num, LOCK_UN) < 0) {
                perror("flock LOCK_UN");
                exit(EXIT_FAILURE);
            }
            close(fd_sum);
            close(fd_num);
            exit(EXIT_SUCCESS);
        } 
    }

    for (int i = 0; i < cnt; i++) wait(NULL);//等待所以子进程都结束
    
    //父进程打印累加和
    printf("sum = %d\n", getNum(fd_sum));
    close(fd_sum);
    close(fd_num);
    return ;
}

int getFD(const char *pathname) {
    int fd = open(pathname, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    return fd;
}

int getNum(int fd) {
    lseek(fd, 0, SEEK_SET);
    int num = 1;
    read(fd, &num, sizeof(int));
    return num;
}

void setNum(int fd, int num) {
    lseek(fd, 0, SEEK_SET);
    write(fd, &num, sizeof(int));
    return ;
}
