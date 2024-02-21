/*************************************************************************
	> File Name: 02.writer_reader.c
	> Author: 
	> Mail: 
	> Created Time: Tue 06 Feb 2024 03:36:42 PM CST
 ************************************************************************/

#include "./common/head.h"


int count = 0, r_num, w_num = 0, w_sleep = 0;
semaphore mutex, w, rw;

void Usage(const char *arg0) {
    fprintf(stderr, "Usgae : %s -w writer_num -r reader_num -W writer_sleep_time !\n", arg0);
    exit(1);
}


void *reader(void *arg) {
    int id = *(int *)arg;
    rsleep(2 * (id + 1));
    free((int *)arg);
    DBG(GREEN"Reader "BLUE"%d"NONE" started!\n", id);
    P(w);
    P(mutex);
    if (count == 0) {
        DBG(GREEN"Reader "BLUE"%d"NONE"is the "RED"first "NONE "reader...\n", id);
        P(rw);
        DBG(GREEN"Reader "BLUE"%d "NONE"got the "RED"rw" NONE " lock...\n", id);
    }
    count++;
    V(mutex);
    V(w);
    rsleep(10);
    DBG(GREEN"Reader "BLUE"%d "PINK" finshed reading!\n"NONE, id);
    P(mutex);
    count--;
    if (count == 0) {
        DBG(GREEN"Reader "RED"%d "NONE"is last reader...\n", id);
        V(rw);
        DBG(GREEN"Reader "RED"%d "NONE"realase the rw lock...\n", id);
    }

    V(mutex);
    DBG(GREEN"Reader "RED"%d "NONE"is ends!\n", id);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    free((int *)arg);
    rsleep(2 * (id + 1));
    DBG(GREEN"Writer "BLUE"%d "NONE"is started!\n", id);
    P(w);
    P(rw);
    DBG(GREEN"Writer "RED"%d"NONE"got the rw lock...\n", id);
    rsleep(12);
    DBG(GREEN"Writer "RED"%d "NONE"finshed the write !\n", id);
    V(rw);
    DBG(GREEN"Writer "RED"%d "NONE"realase the rw lock...\n", id);
    V(w);
    return NULL;
}


int main(int argc, char **argv) {
    int opt;
    if (argc == 1) Usage(argv[0]);
    
    while ((opt = getopt(argc, argv, "w:r:W:")) != -1) {
        switch (opt) {
            case 'r':
                r_num = atoi(optarg);
                break;
            case 'w':
                w_num = atoi(optarg);
                break;
            case 'W':
                w_sleep = atoi(optarg);
                break;
            default:
                Usage(argv[0]);
        }
    }

    mutex = make_semaphore(1);
    w = make_semaphore(1);
    rw = make_semaphore(1);
    
    DBG(PINK"Readers will be started in" RED"%d"NONE"secs.\n", 5);
    DBG(PINK"Writers will be started in" RED"%d"NONE"secs.\n", w_sleep);

    for (int i = 0; i < r_num; i++) {
        pthread_t tid;
        int *id = (int *)calloc(sizeof(int), 1);
        *id = i;
        pthread_create(&tid, NULL, reader, (void *)id);
    }

    for (int i = 0; i < w_num; i++) {
        pthread_t tid;
        int *id = (int *)calloc(sizeof(int), 1);
        *id = i;
        pthread_create(&tid, NULL, writer, (void *)id);
    }
    sleep(100);
    return 0;
}
