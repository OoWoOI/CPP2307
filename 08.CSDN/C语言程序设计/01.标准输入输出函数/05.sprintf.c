/*************************************************************************
	> File Name: 05.sprintf.c
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Apr 2024 08:05:02 PM CST
 ************************************************************************/

#include<stdio.h>
int main() {
    char str[20] = {0};
    int ret = sprintf(str, "hello word\n");
    printf("ret = %d, str = %s", ret, str);
    return 0;
}
