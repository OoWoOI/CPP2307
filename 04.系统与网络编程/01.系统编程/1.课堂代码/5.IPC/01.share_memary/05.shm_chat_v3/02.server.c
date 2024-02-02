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
    pthread_mutex_lock(&share_memory->mutex);//加锁
    if (strlen(share_memory->msg) == 0) {
        pthread_mutex_unlock(&share_memory->mutex);//解锁
        return ;
    }
    printf("[%s] : %s\n", share_memory->name, share_memory->msg);
    memset(share_memory->msg, 0, sizeof(share_memory->msg));//将共享内存重置为空;
    memset(share_memory->name, 0, sizeof(share_memory->name));
    pthread_cond_signal(&share_memory->cond);
    pthread_mutex_unlock(&share_memory->mutex);//解锁
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

    //创建共享内存后就可以开始完成，信息读取的功能
    
    //初始化线程锁
    pthread_mutexattr_t m_attr;
    pthread_mutexattr_init(&m_attr);
    pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&share_memory->mutex, &m_attr);
    pthread_cond_init(&share_memory->cond, NULL);
    //设置服务端进程号、与名字
    pthread_mutex_lock(&share_memory->mutex);//加锁
    share_memory->server_pid = getpid();
    pthread_mutex_unlock(&share_memory->mutex);//解锁

    //next
    signal(SIGUSR1, output);//信号事件触发处理机制注册

    while (1) {
//        output(share_memory);
        sleep(1);//休眠一秒
    }


    return 0;
}
