/*************************************************************************
	> File Name: 02.sscanf.c
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Apr 2024 07:15:52 PM CST
 ************************************************************************/

#include<stdio.h>
int main() {
    char str[20] = "24";
    int a;
    int ret = sscanf(str,"%d", &a);
    printf("ret = %d, a = %d\n", ret, a);
    return 0;
}
