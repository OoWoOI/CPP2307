/*************************************************************************
	> File Name: pthread_pool.h
	> Author: 
	> Mail: 
	> Created Time: Fri 02 Feb 2024 11:49:18 PM CST
 ************************************************************************/

#ifndef _PTHREAD_POOL_H
#define _PTHREAD_POOL_H
struct task_queue {
    int size;
    int total;
    int head;
    int tail;
    char **data;
    pthread_mutex_t mutex;//线程锁
    pthread_cond_t cond;//条件变量
};

void task_queue_init(struct task_queue *tq, int size);
void task_queue_push(struct task_queue *tq, char *str);
char *task_queue_pop(struct task_queue *tq);

void *thread_run(void *arg);

#endif
