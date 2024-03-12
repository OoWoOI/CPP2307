/*************************************************************************
	> File Name: 271.滑动窗口.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 Mar 2024 09:59:56 PM CST
 ************************************************************************/

#include<stdio.h>
#define MAX_N 300000
int arr[MAX_N + 5];
int que[MAX_N + 5];
int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; i++) scanf("%d", &arr[i]);
    //求最小值
    int head = 0, tail = 0;
    for (int i = 1; i <= N; i++) {
        while (tail - head && arr[i] < arr[que[tail - 1]]) tail--;
        que[tail++] = i;
        if (i < K) continue;
        i != K && printf(" ");
        if (i - que[head] >= K) head++;
        printf("%d", arr[que[head]]);
    }
    printf("\n");
    
    //求最大值
    head = 0, tail = 0;

    for (int i = 1; i <= N; i++) {
        while (tail - head && arr[i] > arr[que[tail - 1]]) tail--;
        que[tail++] = i;
        if (i < K) continue;
        i != K && printf(" ");
        if (i - que[head] >= K) head++;
        printf("%d", arr[que[head]]);
    }
    printf("\n");
    return 0;
}
