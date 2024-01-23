/*************************************************************************
	> File Name: 02.my_cp.c
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2024 09:04:33 PM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage : %s file1 file2", argv[0]);
        exit(1);
    }
    char file1[20] = {0};
    char file2[20] = {0};
    int fd1, fd2;
    strcpy(file1, argv[1]);
    strcpy(file2, argv[2]);

    if ((fd1 = open(file1, O_RDONLY)) == -1) {
        perror("open file1");
        exit(1);
    }

    //if ((fd2 = open(file2, O_CREAT | O_EXCL | O_WRONLY, 0644)) < 0) {
    if ((fd2 = open(file2, O_CREAT | O_WRONLY, 0644)) < 0) {
        perror("open file2");
        exit(1);
    }
    char buff[1024] = {0};
    size_t buff_size = sizeof(buff) - 1;
    while (1) {
        int ret_r = read(fd1, buff, buff_size);
        if (ret_r < 0) {
            perror("read");
            exit(1);
        }

        if (ret_r == 0) {
            break;
        }
        //printf("%s", buff);
        int ret_w = write(fd2, buff, ret_r);
        if (ret_w < 0) {
            perror("write");
            exit(1);
        }
        memset(buff, 0, buff_size);
    }
    close(fd1);
    close(fd2);
    return 0;
}
