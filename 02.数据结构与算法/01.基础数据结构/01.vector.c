/*************************************************************************
	> File Name: 01.vector.c
	> Author: 
	> Mail: 
	> Created Time: Sat 09 Mar 2024 08:41:42 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int data_type;

typedef struct vector {
    data_type* data;
    int size;
    int length;
}vector;

vector *init(int size) {
    vector *vec = (vector *)calloc(sizeof(vector), 1);
    vec->data = (data_type *)calloc(sizeof(data_type), size);
    vec->size = size;
    vec->length = 0;
    return vec;
}

int expand(vector *vec) {
    int exp_size = vec->size;
    data_type *p = NULL;
    while (exp_size) {
        p = (data_type *)realloc(vec->data, exp_size + vec->size);
        if (p) break;
        exp_size /= 2; 
    }

    if (!p) return 0;
    vec->size += exp_size;
    vec->data = p;
    return 1;
}

int insert(vector *vec, int ind, data_type val) {
    if (ind < 0 || ind > vec->length) return 0;
    if (vec->length >= vec->size) {
        //扩容
        if (!expand(vec)) return 0;
        printf("expand success ! => size = %d\n", vec->size);
    }
    for (int i = vec->length; i > ind; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[ind] = val;
    vec->length++;
    return 1;
}

int erase(vector *vec, int ind) {
    if (!vec || (ind < 0 || ind >= vec->length)) return 0;
    for (int i = ind; i < vec->length - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->length--;
    return 1;
}

int find(vector *vec, int ind) {
    return (ind < 0 || ind >= vec->length) ? -1 : vec->data[ind];
}

int update(vector *vec, int ind, data_type val) {
    return (ind < 0 || ind >= vec->length) ? -1 : (vec->data[ind] = val);
}

void clear(vector *vec) {
    if (!vec) return ;
    free(vec->data);
    free(vec);
    return ;
}

void output(vector *vec) {
    if (!vec) return ;
    printf("| vec => | total = %d | [ ", vec->length);
    for (int i = 0; i < vec->length; i++) {
        i && printf(", ");
        printf("%d", vec->data[i]);
    }
    printf(" ]\n");
    return ;
}

int main() {
    #define max_op 20
    srand(time(0));//随机种子
    int size = 5;
    vector *vec = init(size);
    for (int i = 0; i < max_op; i++) {
        int op = rand() % 6;
        int val = rand() % 100;
        int ind = rand() % (vec->length + 3) - 1;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert val = %d to ind = %d in vec = %d\n", val, ind, insert(vec, ind, val));
            } break;
            case 3: {
                printf("erase ind = %d from vec = %d\n", ind, erase(vec, ind));
            } break;
            case 4: {
                printf("find ind = %d in vec val = %d\n", ind, find(vec, ind));
            } break;
            case 5: {
                printf("update ind %d in vec val = %d\n", ind, update(vec, ind, val));
            } break;
        }
        output(vec);
    }
    #undef max_op
    clear(vec);
    return 0;
}
