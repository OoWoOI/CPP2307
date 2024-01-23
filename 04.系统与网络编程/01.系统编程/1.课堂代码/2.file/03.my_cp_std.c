/*************************************************************************
	> File Name: 03.my_cp_std.c
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2024 10:50:33 PM CST
 ************************************************************************/

#include "./common/head.h"

int main(int argc, char **argv) {
    FILE *fp_in, *fp_out;
    if (argc != 3) {
        fprintf(stderr, "Usage : %s file1 file2\n", argv[0]);
        exit(1);
    }
    if ((fp_in = fopen(argv[1], "r+")) == NULL) {
        perror("fopen file1");
        exit(1);
    }

    if ((fp_out = fopen(argv[2], "w+")) == NULL) {
        perror("fopen file2");
        exit(1);
    }

    char buff[1024] = {0};
    size_t buff_size = sizeof(buff) - 1;
    int ret_in;
    while ((ret_in = fread(buff, sizeof(char), buff_size, fp_in)) != 0) {
       int ret_out = fwrite(buff, sizeof(char), ret_in, fp_out);
        if (ret_out < 0) {
            perror("fwrite");
            exit(1);
        }
        memset(buff, 0, buff_size); 
    }
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}

