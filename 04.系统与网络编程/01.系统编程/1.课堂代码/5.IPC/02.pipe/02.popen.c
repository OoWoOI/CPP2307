/*************************************************************************
	> File Name: 02.popen.c
	> Author: 
	> Mail: 
	> Created Time: Thu 01 Feb 2024 04:05:00 PM CST
 ************************************************************************/

#include "./common/head.h"

int main() {
    FILE *fp = popen("cat ./02.popen.c", "r");
    char buff[1024] = {0};

    while (fgets(buff, 1024, fp) != NULL) {
        printf("%s", buff);
    }

    pclose(fp);
    return 0;
}

