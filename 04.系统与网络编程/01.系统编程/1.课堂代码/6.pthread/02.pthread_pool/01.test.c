/*************************************************************************
	> File Name: 01.test.c
	> Author: 
	> Mail: 
	> Created Time: Fri 02 Feb 2024 11:48:58 PM CST
 ************************************************************************/

#include "./common/head.h"
#include "./pthread_pool.h"

#define PTHREAD_NUM 10
#define QUEUE_SIZE 100


int main() {
    pthread_t tid[PTHREAD_NUM + 5];
    struct task_queue tq;
    task_queue_init(&tq, QUEUE_SIZE);
    for (int i = 0; i < PTHREAD_NUM; i++) {
        pthread_create(&tid[i], NULL, thread_run, (void *)&tq);
    }
    char buff[QUEUE_SIZE + 5][1024] = {0};
    int sub = 0;
    while (1) {
        //打开文件
        FILE *fp = fopen("./pthread_pool.c", "r");
        if (fp == NULL) {
            perror("open");
            exit(1);
        }
        while (fgets(buff[sub], 1024, fp) != NULL) {
            task_queue_push(&tq, buff[sub++]);
            if (sub >= QUEUE_SIZE) sub = 0;
        }

        if (tq.total == tq.size) {
            while (1) {
                usleep(10000);
                if (tq.total < tq.size) break;
            }
            sleep(1);
        }

        fclose(fp);
    }

    return 0;
}
