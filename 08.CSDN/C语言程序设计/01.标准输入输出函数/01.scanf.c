/*************************************************************************
	> File Name: 01.scanf.c
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Apr 2024 07:02:34 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int a;
    int ret = scanf("%d", &a);//标准输入函数
    printf("ret = %d, a = %d\n", a, ret);
    return 0;
}
