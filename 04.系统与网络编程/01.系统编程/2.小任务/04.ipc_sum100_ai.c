/*************************************************************************
	> File Name: 04.test.c
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Jan 2024 05:17:03 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

#define FILENAME "sumfile"

int getSum(int fd) {
    lseek(fd, 0, SEEK_SET); // 将文件指针移回文件开头
    int sum;
    read(fd, &sum, sizeof(int));
    return sum;
}

void setSum(int fd, int sum) {
    lseek(fd, 0, SEEK_SET); // 将文件指针移回文件开头
    write(fd, &sum, sizeof(int));
}

void childProcess(int fd, int start, int end) {
    int sum = getSum(fd);
    for (int i = start; i <= end; ++i) {
        sum += i;
    }

    flock(fd, LOCK_EX); // 获取文件锁
    setSum(fd, sum);
    flock(fd, LOCK_UN); // 释放文件锁
}

int main() {
    int fd = open(FILENAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("文件打开失败");
        exit(EXIT_FAILURE);
    }

    int sum = 0;
    write(fd, &sum, sizeof(int)); // 初始化文件内容为0

    const int numProcesses = 5; // 假设有5个子进程
    const int numbersPerProcess = 20; // 每个子进程累加的数字范围

    for (int i = 0; i < numProcesses; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("生成子进程错误");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // 子进程
            int start = i * numbersPerProcess + 1;
            int end = (i + 1) * numbersPerProcess;

            childProcess(fd, start, end);

            close(fd); // 子进程用完文件后关闭文件描述符
            exit(EXIT_SUCCESS);
        }
    }

    // 父进程等待所有子进程结束
    for (int i = 0; i < numProcesses; ++i) {
        wait(NULL);
    }

    sum = getSum(fd);
    printf("累加和：%d\n", sum);

    close(fd); // 关闭文件描述符

    return 0;
}

