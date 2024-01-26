/*************************************************************************
	> File Name: 01.test.c
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Jan 2024 08:46:09 PM CST
 ************************************************************************/

#include "head.h"
int main() {
    int age = 19;
    char name[20] = "suyelu";
    DBG("this is Debug information.\n");
    DBG("%s is %d years old.\n", name, age);
 //   DBG(CLEAR"这是绿色\n"); 
    log_event(LOG_LEVEL_WARNING, "测试1", "./log");
    return 0;
}
