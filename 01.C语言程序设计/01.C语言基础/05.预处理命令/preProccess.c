/*************************************************************************
	> File Name: preProccess.c
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Apr 2024 09:04:39 PM CST
 ************************************************************************/

#include<stdio.h>

#define str(a) {\
    printf("%s : %d\n", #a, a);\
}

char *usr;
char *phone;
__attribute__((constructor))
void init() {
    usr = "mofei";
    phone = "132312123";
    return ;
}


int main() {
    printf("usr : %s \nphone : %s\n", usr, phone);
    int A = 123;
    str(A);
    return 0;
}
