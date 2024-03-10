/*************************************************************************
	> File Name: threadpool.h
	> Author: 
	> Mail: 
	> Created Time: Mon 26 Feb 2024 04:13:23 PM CST
 ************************************************************************/

#ifndef _THREADPOOL_H
#define _THREADPOOL_H
//线程池化技术头文件
struct task_queue {
    int size;
    int total;
    int head, tail;
    void **data;
    pthread_mutex_t mutex;//线程锁
    pthread_cond_t cond;//条件变量
};

void task_queue_init(struct task_queue *tq, int size);//初始化任务队列
void task_queue_push(struct task_queue *tq, void *elem);//将元素入队
void *task_queue_pop(struct task_queue *tq);//将元素出队
void task_queue_clear(struct task_queue *tq);//销毁任务队列
void *thread_run(void *arg);


#endif
