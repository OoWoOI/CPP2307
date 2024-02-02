/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Tue 30 Jan 2024 09:05:05 PM CST
 ************************************************************************/

#include "./common/head.h"
#include "./chat.h"


struct MSG * share_memory = NULL;

int main(int argc, char **argv) {
    
    //获取服务端的共享内存
    key_t key;
    if ((key = ftok(".", 1025)) < 0) {
        perror("ftok");
        exit(1);
    }
    int shmid;
    if ((shmid = shmget(key, sizeof(struct MSG), 0)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((share_memory = shmat(shmid, NULL, 0)) == NULL) {
        perror("shmat");
        exit(1);
    }
    //获取用户名
    char name[20] = {0};
    int opt;
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                strcpy(name, optarg);
                break;
            default :
                fprintf(stderr, "Usage : %s is - n username !\n", argv[0]);
                exit(1);
        }
    }
    
    //向服务器发送数据
    while (1) {
        //sleep(1); 
        strcpy(share_memory->name, name);
        printf("[%s] Please enter : ", name);
        char msg[1024] = {0};
        int ret = scanf("%[^\n]s", msg);
        getchar();
        if (ret == 0) continue;
  /**  a: pthread_mutex_lock(&share_memory->mutex);
        if (strlen(share_memory->msg)) {
            pthread_mutex_unlock(&share_memory->mutex);
            goto a;
        }**/
        pthread_mutex_lock(&share_memory->mutex);
        while (strlen(share_memory->msg) != 0)
            pthread_cond_wait(&share_memory->cond, &share_memory->mutex);        
        strcpy(share_memory->name, name);
        strcpy(share_memory->msg, msg);
        pthread_mutex_unlock(&share_memory->mutex);
        kill(share_memory->server_pid, SIGUSR1);
    }
    
    return 0;
}

