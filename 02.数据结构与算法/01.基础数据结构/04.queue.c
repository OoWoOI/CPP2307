/*************************************************************************
	> File Name: 04.queue.c
	> Author: 
	> Mail: 
	> Created Time: Sun 10 Mar 2024 05:20:13 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef int data_t;

typedef struct queue {
    data_t *data;
    int head;
    int tail;
    int size;
    int cnt;
}queue;


queue* init(int size) {
    queue *que = (queue *)calloc(sizeof(queue), 1);
    que->data = (data_t *)calloc(sizeof(data_t), size);
    que->head = que->tail = 0;
    que->size = size;
    que->cnt = 0;
    return que;
}

int empty(queue *que) {
    return que->cnt == 0;
}

int push(queue *que, data_t val) {
    if (que == NULL) return 0;
    if (que->cnt >= que->size) return 0;
    que->data[que->tail] = val;
    if (++que->tail >= que->size) que->tail = 0;
    que->cnt++;
    return 1;
}

data_t pop(queue *que) {
    if (que == NULL) return -1;
    if (empty(que)) return -1;
    data_t elem = que->data[que->head];
    if (++que->head >= que->size) que->head = 0;
    que->cnt--;
    return elem;
}

data_t front(queue *que){
    return empty(que) ? -1 : que->data[que->head];
}

void output(queue *que) {
    if (que == NULL) return ;
    printf("queue : [");
    for (int i = 0, j = que->head; i < que->cnt; i++) {
        i && printf(", ");
        printf("%d", que->data[j]);
        if (++j == que->size) j = 0; 
    }
    printf("]\n");
    return ;
}

void clear(queue *que) {
    if (que == NULL) return ;
    if (que->data) free(que->data);
    free(que);
    return ;
}

int main() {
    #define max_op 20
    int op, val;
    srand(time(0));
    queue *que = init(max_op);
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1: {
                printf("push val[%d] into queue stat[%d] !\n", val, push(que, val));
            } break;
            case 2: {
                printf("pop val from queue elem[%d] !\n", pop(que));
            } break;
            case 3: {
                printf("get front elem from queue : [%d] !\n", front(que));
            } break;
        }
        output(que);

    }
    #undef max_op
    clear(que);    
    
    return 0;
}
