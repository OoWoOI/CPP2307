/*************************************************************************
	> File Name: 04.printf.c
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Apr 2024 07:46:25 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main() {
    int a;
    while (~scanf("%d", &a)) {
        printf(" has %d digits\n", printf("%d", a));
    }
    return 0;
}
