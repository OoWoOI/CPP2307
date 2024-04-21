/*************************************************************************
	> File Name: 06.fprintf.c
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Apr 2024 08:14:43 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main() {
    FILE *fp = NULL;
    if ((fp = fopen("./output.txt", "w+")) == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    int ret = fprintf(fp, "hello word\n");
    printf("ret = %d\n", ret);
    fclose(fp);
    return 0;
}
