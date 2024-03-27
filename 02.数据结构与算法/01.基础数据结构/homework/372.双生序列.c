/*************************************************************************
	> File Name: 372.双生序列.c
	> Author: 
	> Mail: 
	> Created Time: Wed 13 Mar 2024 04:31:56 PM CST
 ************************************************************************/

#include<stdio.h>

#define MAX_N 500000
int N, P = 1;
int a[MAX_N + 5], b[MAX_N + 5];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }
    int top1 = -1, top2 = -1;
    while (P < N) {
        while (top1 != -1 && a[top1] >= a[P]) top1--;
        while (top2 != -1 && b[top2] >= b[P]) top2--;
        if (top1 - top2) break;
        a[++top1] = a[P];
        b[++top2] = b[P];
        P++;
    }
    printf("%d\n", P);
    return 0;
}
