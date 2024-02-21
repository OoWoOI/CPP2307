/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Jan 2024 09:11:23 PM CST
 ************************************************************************/

#include "./head.h"

void rsleep(double sec) {
    long max = sec * 1000000;
    srand((unsigned)time(0));
    long value = rand();
    usleep(value % max);
}

void perror_exit(const char *msg) {
    perror(msg);
    exit(1);
}

semaphore make_semaphore(int value) {
    semaphore sem = malloc(sizeof(semaphore));
    int ret = sem_init(sem, 0, value);
    if (ret != 0) {
        perror("sem_init failed !");
        exit(1);
    }

    return sem;
}

void P(semaphore sem) {
    int ret = sem_wait(sem);

    if (ret != 0) {
        perror("sem_wait failed !");
        exit(1);
    }
    
    return ;
}

void V(semaphore sem) {
    int ret = sem_post(sem); 
    if (ret != 0) perror_exit("sem_post");
    return ;
}


//修改文件述符
int make_block(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    flag &= ~O_NONBLOCK;
    return fcntl(fd, F_SETFL, flag);
}

int make_nonblock(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    flag |= O_NONBLOCK;
    return fcntl(fd, F_SETFL, flag);
}


//日志系统
void log_event(int level, const char *message, const char *filename) {
    time_t now = time(NULL);
    char *level_str;
    FILE *fp;

    switch (level) {
        case LOG_LEVEL_INFO:
            level_str = "INFO";
            break;
        case LOG_LEVEL_WARNING:
            level_str = "WARNING";
            break;
        case LOG_LEVEL_ERROR:
            level_str = "ERROR";
            break;
        default :
            level_str = "UNKNOWN";
            break;
    }

    fp = fopen(filename, "a");
    //ToDO: 确认是否正常打开
    if (fp != NULL) {
        fprintf(fp, "%s [%s] :  %s \n", ctime(&now), level_str, message);
        fclose(fp);
    }
    return ; 
}
