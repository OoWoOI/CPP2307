/*************************************************************************
	> File Name: 03.fscanf.c
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Apr 2024 07:28:47 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main() {
    FILE *fp = NULL;
    if ((fp = fopen("./input.txt", "r+")) == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    int a;
    int ret = fscanf(fp, "%d", &a);
    printf("ret = %d, a = %d\n", ret, a);
    fclose(fp);
    return 0;
}
