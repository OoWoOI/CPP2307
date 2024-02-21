/*************************************************************************
	> File Name: 01.producer_consumer.c
	> Author: 
	> Mail: 
	> Created Time: Tue 06 Feb 2024 03:31:28 PM CST
 ************************************************************************/

#include "./common/head.h"


void *producer_work(void *arg);//生产者工作流
void *consumer_work(void *arg);//消费者工作流

void Usage(char *msg) {
    fprintf( stderr, "Usage : %s -p producer_num -c consumer_num -b buffersize\n", msg);
    exit(1);
}

int *buff;

int p_num = 1, c_num = 1, buffersize = 100, buff_now = 0, now = 0;

//信号量
semaphore mutex, full, empty;

int main(int argc, char **argv) {
    if (argc != 7) Usage(argv[0]);
    int opt;

    while ((opt = getopt(argc, argv, "p:c:b:")) != -1) {
        switch (opt) {
            case 'p':
                p_num = atoi(optarg);
                break;
            case 'c':
                c_num = atoi(optarg);
                break;
            case 'b':
                buffersize = atoi(optarg);
                break;
            default:
                Usage(argv[0]);
        }
    }
    
    mutex = make_semaphore(1);
    full = make_semaphore(0);
    empty = make_semaphore(buffersize);

    buff = (int *)calloc(sizeof(int), buffersize);
    
    //具体的工作逻辑
    for (int i = 0; i < p_num; i++) {//生产者
        pthread_t tid;
        pthread_create(&tid, NULL, producer_work, NULL);
    }
    for (int i = 0; i < c_num; i++) {//消费者
        pthread_t tid;
        pthread_create(&tid, NULL, consumer_work, NULL);
    }
   sleep(100); 
    return 0;
}

void *producer_work(void *arg) {
    while (1) {
        rsleep(0.5);
        DBG(YELLOW"生产了一个商品!\n"NONE);
        P(empty);
        P(mutex);//获取锁
        buff[buff_now++] = now++;
        DBG(RED"Producer"NONE"-> %d, %d numbers in buff!\n", now, buff_now);
        V(mutex);//释放锁
        V(full);
    }
    return NULL;
}

void *consumer_work(void *arg) {
    while (1) {
        P(full);
        P(mutex);
        DBG(GREEN"Consumer"NONE"->%d, %d numbers in buff!\n", buff[buff_now - 1], buff_now - 1);
        buff[--buff_now] = 0;
        V(mutex);
        V(empty);
        rsleep(0.7);
    } 
    return NULL;
}

