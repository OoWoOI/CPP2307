/*************************************************************************
	> File Name: threadpool.c
	> Author: 
	> Mail: 
	> Created Time: Mon 26 Feb 2024 04:12:56 PM CST
 ************************************************************************/

#include "head.h"

void task_queue_init(struct task_queue *tq, int size) {
    tq->size = size;
    tq->total =  tq->head = tq->tail = 0;
    tq->data = (void **)calloc(sizeof(void *), size + 5);

    //初始化锁和条件变量
    if ((pthread_mutex_init(&tq->mutex, NULL)) < 0) {
        perror("pthread_mutex_init");
        exit(1);
    }

    if ((pthread_cond_init(&tq->cond, NULL)) < 0) {
        perror("pthread_cond_init");
        exit(1);
    }

    return ;
}

void task_queue_push(struct task_queue *tq, void *elem) {
    pthread_mutex_lock(&tq->mutex);//获取锁
    if (tq->total == tq->size) {
        fprintf(stderr, "task_queue is full!\n");
        pthread_mutex_unlock(&tq->mutex);
        return ;
    }
    tq->data[tq->tail] = elem;
    if (++tq->tail == tq->size) tq->tail = 0;
    tq->total++;
    pthread_cond_signal(&tq->cond);//向条件变量发送信号
    pthread_mutex_unlock(&tq->mutex);//释放锁
    return ;
}

void *task_queue_pop(struct task_queue *tq) {
    pthread_mutex_lock(&tq->mutex);
    while (tq->total == 0) {
        pthread_cond_wait(&tq->cond, &tq->mutex);
    }
    void *elem = tq->data[tq->head];
    if (++tq->head == tq->size) tq->head = 0;
    tq->total--;
    pthread_mutex_unlock(&tq->mutex);
    return elem;
}

void task_queue_clear(struct task_queue *tq) { 
    for (int i = 0; i < tq->size; i++) {
        if (!tq->data[i]) continue;
        free(tq->data[i]);
    }
    free(tq->data);
    tq->size = tq->total = tq->head = tq->tail = 0;
    pthread_mutex_destroy(&tq->mutex);
    pthread_cond_destroy(&tq->cond);
    free(tq);
    return ;
}




