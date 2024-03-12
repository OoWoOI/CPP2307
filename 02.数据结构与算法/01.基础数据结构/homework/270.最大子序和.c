/*************************************************************************
	> File Name: 270.最大子序和.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 Mar 2024 11:21:09 PM CST
 ************************************************************************/

#include<stdio.h>
#include<inttypes.h>

#define MAX_N 300000

int S[MAX_N + 5];
int que[MAX_N + 5], head = 0, tail = 0;
int ans = INT32_MIN;

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++ ) {
        scanf("%d", &S[i]);
        S[i] += S[i - 1];
    }

    que[tail++] = 0;
    
    for (int i = 1; i <= N; i++) {
        if (i - que[head] > M) head++;
        ans = ans >= S[i] - S[que[head]] ? ans: S[i] - S[que[head]];
        while (tail - head && S[i] <= S[que[tail - 1]]) tail--;
        que[tail++] = i;
    }
    printf("%d\n", ans);
    return 0;
}
