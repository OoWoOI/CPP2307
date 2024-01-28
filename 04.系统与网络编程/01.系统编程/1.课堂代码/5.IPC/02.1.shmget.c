/*************************************************************************
	> File Name: 02.1.shmget.c
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Jan 2024 10:21:15 PM CST
 ************************************************************************/

#include "./common/head.h"
struct person {
    char name[20];
    int age;
};

int main() {
    struct person *ps = NULL;
    key_t key;
    if ((key = ftok(".", 1024)) < 0) {
        perror("ftok");
        exit(1);
    }
    int shmid;
    if ((shmid = shmget(key, sizeof(struct person), 0)) < 0) {
        perror("shmget");
        exit(1);
    }
    ps = shmat(shmid, NULL, 0);
    printf("name is %s, age is %d\n", ps->name, ps->age);
    
    return 0;
}
