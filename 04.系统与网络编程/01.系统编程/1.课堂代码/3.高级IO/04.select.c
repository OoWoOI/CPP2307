/*************************************************************************
	> File Name: 04.select.c
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jan 2024 04:36:29 PM CST
 ************************************************************************/

#include "./common/head.h"
int main() {
    int age = 18;
    make_nonblock(0);
    fd_set rfds;
    struct timeval tv;

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    
    int ret;
/**
    if ((ret = select(1, &rfds, NULL, NULL, &tv)) <= 0) {
        fprintf(stderr, "Notion read !\n");
    }

    scanf("%d", &age);

    printf("WangDong is %d years old !\n", age);
**/
    while (1) {
        FD_SET(0, &rfds); 
        ret = select(1, &rfds, NULL, NULL, &tv);
        if (ret <= 0) continue;
        if (FD_ISSET(0, &rfds)) scanf("%d", &age);
        printf("age = %d\n", age);
    }

    return 0;
}
