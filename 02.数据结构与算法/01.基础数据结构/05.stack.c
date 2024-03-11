/*************************************************************************
	> File Name: 05.stack.c
	> Author: 
	> Mail: 
	> Created Time: Sun 10 Mar 2024 05:20:20 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef int data_t;

typedef struct stack {
    data_t *data;
    int top;
    int size;
}stack;

stack *init(int size) {
    stack *stk = (stack *)calloc(sizeof(stack), 1);
    stk->data = (data_t *)calloc(sizeof(data_t), size);
    stk->size = size;
    stk->top = -1;
    return stk;
}

int empty(stack *stk) {
    return stk == NULL ? 1 : stk->top == -1;
}

data_t top(stack *stk) {
    if (stk == NULL || stk->top == -1) return -1;
    return stk->data[stk->top];
}

int push(stack *stk, data_t val) {
    if (stk == NULL || stk->top + 1 == stk->size) return 0;
    stk->data[++stk->top] = val;
    return 1;
}

data_t pop(stack *stk) {
    if (empty(stk)) return 0;
    return stk->data[stk->top--];
}

void output(stack *stk) {
    if (stk == NULL) return ;
    printf("stack :\n");
    for (int i = stk->top; i >= 0; i--) {
        i == stk->top && printf("top => ");
        printf("\t| %2d |\n", stk->data[i]);
    }
    printf(" \t ———— \n");
    return ;
}

void clear(stack *stk) {
    if (stk == NULL) return ;
    if (stk->data) free(stk->data);
    free(stk);
    return ;
}

int main() {
    #define max_op 20
    int op, val;
    stack *stk = init(max_op);
    srand(time(0));
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1: {
                printf("push val[%d] to stack stat[%d] !\n", val, push(stk, val));
            } break;
            case 2: {
                printf("pop elem from the stack val[%d] !\n", pop(stk));
            } break;
            case 3:{
                printf("top elem of the stack val[%d] !\n", top(stk));
            } break;
        }
        output(stk);
    }
    #undef max_op
    clear(stk);
    return 0;
}
