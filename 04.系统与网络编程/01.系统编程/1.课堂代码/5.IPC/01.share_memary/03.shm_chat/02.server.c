/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 30 Jan 2024 09:04:39 PM CST
 ************************************************************************/

#include "./common/head.h"
#include "./chat.h"

struct MSG *share_memory = NULL;

void output(int signum) {
    if (strlen(share_memory->name) == 0 || strlen(share_memory->msg) == 0) return ;
    printf("[%s] : %s\n", share_memory->name, share_memory->msg);
    memset(share_memory, 0, sizeof(struct MSG));//将共享内存重置为空;
    return ;
}

int main() {
    //申请一个共享内存, 如果存在就直接使用
    key_t key;
    if ((key = ftok(".", 1025)) < 0) {
        perror("ftok");
        exit(1);
    }
    int shmid;
    if ((shmid = shmget(key, sizeof(struct MSG), IPC_CREAT | 0644)) < 0) {
        perror("shmid");
        exit(1);
    }
    

    if ((share_memory = shmat(shmid, NULL, 0)) == NULL) {
        perror("shmat");
        exit(1);
    }

    //注册一个信号驱动事件
    signal(SIGALRM, output);
    
    struct itimerval itimer;
    itimer.it_value.tv_sec = 10;
    itimer.it_value.tv_usec = 0;
    itimer.it_interval.tv_sec = 1;
    itimer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &itimer, NULL);
    
    //创建共享内存后就可以开始完成，信息读取的功能
    while (1) {
        //output(share_memory);
        sleep(1);//休眠一秒
    }


    return 0;
}
