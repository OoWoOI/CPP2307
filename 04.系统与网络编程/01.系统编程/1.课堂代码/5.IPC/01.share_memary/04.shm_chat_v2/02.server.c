/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 30 Jan 2024 09:04:39 PM CST
 ************************************************************************/

#include "./common/head.h"
#include "./chat.h"

void output(struct MSG *arg) {
    if (strlen(arg->name) == 0 || strlen(arg->msg) == 0) return ;
    printf("[%s] : %s\n", arg->name, arg->msg);
    memset(arg, 0, sizeof(struct MSG));//将共享内存重置为空;
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
    
    struct MSG *share_memory = NULL;

    if ((share_memory = shmat(shmid, NULL, 0)) == NULL) {
        perror("shmat");
        exit(1);
    }

    //创建共享内存后就可以开始完成，信息读取的功能

    while (1) {
        output(share_memory);
        sleep(1);//休眠一秒
    }


    return 0;
}
