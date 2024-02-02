/*************************************************************************
	> File Name: pthread_pool.c
	> Author: 
	> Mail: 
	> Created Time: Fri 02 Feb 2024 11:49:41 PM CST
 ************************************************************************/

#include "./common/head.h"
#include "./pthread_pool.h"

//任务队列初始化
void task_queue_init(struct task_queue *tq, int size) {
    tq->head = tq->tail = tq->total = 0;
    tq->size = size;
    pthread_mutex_init(&tq->mutex, NULL);
    pthread_cond_init(&tq->cond, NULL);
    tq->data = calloc(sizeof(void *), size);
    return ;
}

//任务队列入队
void task_queue_push(struct task_queue *tq, char *str) {
    pthread_mutex_lock(&tq->mutex);
    if (tq->total == tq->size) {
        pthread_mutex_unlock(&tq->mutex);
        return ;
    }
    tq->data[tq->tail] = str;
    tq->total++;
    if (++tq->tail == tq->size) {
        tq->tail = 0;
    }
    pthread_cond_signal(&tq->cond);
    pthread_mutex_unlock(&tq->mutex);
    return ;
}

char *task_queue_pop(struct task_queue *tq) {
    pthread_mutex_lock(&tq->mutex);
    while (tq->total == 0) {
        pthread_cond_wait(&tq->cond, &tq->mutex);
    }

    char *str = tq->data[tq->head];
    if (++tq->head == tq->size) {
        tq->head = 0;
    }

    tq->total--;
    pthread_mutex_unlock(&tq->mutex);

    return str;
}

void *thread_run(void *arg) {
    pthread_detach(pthread_self());//分离线程
    struct task_queue *tq = (struct task_queue *)arg;
    while (1) {
        char *str = task_queue_pop(tq);
        printf("%s", str);
    }
    return NULL;
}
