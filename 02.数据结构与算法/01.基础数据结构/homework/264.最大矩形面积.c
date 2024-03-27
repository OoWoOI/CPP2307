/*************************************************************************
	> File Name: 264.最大矩形面积.c
	> Author: 
	> Mail: 
	> Created Time: Wed 13 Mar 2024 03:39:32 PM CST
 ************************************************************************/

#include<stdio.h>
#define MAX_N 100000

long long l[MAX_N + 5];
long long r[MAX_N + 5], stk[MAX_N + 5];
long long S[MAX_N + 5], ans = 0;
int main() {
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &S[i]);
    }
    l[0] = -1, l[N + 1] = -1;
    r[0] = -1, r[N + 1] = -1;
    int top = 0;
    stk[top = 0] = 0;
    //从左往右
    for (int i = 1; i <= N; i++) {
        while (S[stk[top]] >= S[i]) top--;
        l[i] = stk[top];
        stk[++top] = i;
    }
    stk[top = 0] = 0;
    //从右往左
    for (int i = N; i >= 1; i--) {
        while (S[stk[top]] >= S[i]) top--;
        r[i] = stk[top];
        stk[++top] = i;
    }

    //计算
    for (int i = 1; i <= N; i++) {
        ans = ans >= S[i] * (r[i] - l[i] - 1) ? ans : S[i] * (r[i] - l[i] - 1);
    }
    printf("%lld\n", ans);
    return 0;
}
