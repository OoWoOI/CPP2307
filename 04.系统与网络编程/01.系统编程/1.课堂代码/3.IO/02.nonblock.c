/*************************************************************************
	> File Name: 02.nonblock.c
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jan 2024 03:43:31 PM CST
 ************************************************************************/

#include "./common/head.h"
int main() {
    int age, ret;
    make_nonblock(0);
    int cnt = 0;
    while (1) {
        if (++cnt >= 30) break;
        int ret = scanf("%d", &age);
        if (ret > 0) break;
        sleep(1);
    }

    printf("WangDong is %d years old !\n", age);

    return 0;
}
