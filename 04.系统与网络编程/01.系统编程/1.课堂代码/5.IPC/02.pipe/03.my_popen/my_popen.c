/*************************************************************************
	> File Name: my_popen.c
	> Author: 
	> Mail: 
	> Created Time: Thu 01 Feb 2024 04:38:01 PM CST
 ************************************************************************/

#include "./common/head.h"

static pid_t  *cpid = NULL;
static int maxsize = 0;

FILE *my_popen(const char *cmd, const char *type) {
    pid_t pid;
    int pfd[2];
    FILE *fp;
    
    if ((type[0] != 'r') && type[0] != 'w' || type[1] != '\0') {
        errno = EINVAL;
        return NULL;
    }

    if (cpid == NULL) {
        maxsize = sysconf(_SC_OPEN_MAX);
        if ((cpid = (pid_t *)calloc(maxsize, sizeof(pid_t))) == NULL) {
            return NULL;
        }
    }

    if (pipe(pfd) < 0) {
        return NULL;
    }

    if ((pid = fork()) < 0) {
        return NULL;
    }

    if (pid == 0) {
        if (type[0] == 'r') {
            close(pfd[0]);
            if (pfd[1] != STDOUT_FILENO) {
                dup2(pfd[1], STDOUT_FILENO);
                close(pfd[1]);
            }
        } else {
            close(pfd[1]);
            if (pfd[0] != STDOUT_FILENO) {
                dup2(pfd[0], STDOUT_FILENO);
                close(pfd[0]);
            }
        }
        execl("/bin/sh", "sh", "-c", cmd, NULL);

    } 

    if (type[0] == 'r') {
        close(pfd[1]);
        if ((fp = fdopen(pfd[0], type)) == NULL) {
            return NULL;
        }
    } else {
        close(pfd[0]);
        if ((fp = fdopen(pfd[1], type)) == NULL) {
            return NULL;
        }
    }

    cpid[fileno(fp)] = pid;

    return fp;
}


int my_pclose(FILE *fp) {
    int wstatus;
    pid_t pid;
    pid = cpid[fileno(fp)];
    if (pid == 0) {
        errno = EINVAL;
        return -1;
    }
    fflush(fp);
    fclose(fp);
    wait4(pid, &wstatus, 0, NULL);
    return wstatus;
}
