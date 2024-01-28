/*************************************************************************
	> File Name: 01.pthread.c
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Jan 2024 11:01:14 PM CST
 ************************************************************************/

#include "./common/head.h"

struct person {
    char name[20];
    int age;
};

void *pthread_run(void *arg) {
    int *p = (int *)arg;
    printf("wangdongdong is %d years old !\n", *p);
    return NULL;
}

int main() {
    pthread_t tid;
    int age = 18;
    pthread_create(&tid, NULL, pthread_run, (void *)&age);
    usleep(100);

    return 0;
}
