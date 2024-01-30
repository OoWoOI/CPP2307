/*************************************************************************
	> File Name: 02.shmget.c
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Jan 2024 09:18:33 PM CST
 ************************************************************************/

#include "./common/head.h"

struct shm_person {
    char name[20];
    int age;
};

int main() {
    struct shm_person *share_memary = NULL;
    pid_t pid;
    key_t key = ftok(".", 1024);
    int shmid = shmget(key, sizeof(struct shm_person), IPC_CREAT | 0644);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    } 
    share_memary = shmat(shmid, NULL, 0);
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        //子进程处理
        sleep(1);
        printf("name = %s, age = %d\n", share_memary->name, share_memary->age);
    } else {
        //父进程处理
        strcpy(share_memary->name, "WangDong");
        share_memary->age = 18;
    }



    return 0;
}
