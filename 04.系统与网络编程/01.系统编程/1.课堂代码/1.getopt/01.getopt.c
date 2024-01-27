/*************************************************************************
	> File Name: 01.getopt.c
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2024 06:36:34 PM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    char output[20] = {0};
    char input[20] = {0};
    int opt;

    if (argc < 2) {
        fprintf(stderr, "Usage : %s -o file\n", argv[0]);
        //return -1;
        exit(1);
    }

    while ((opt = getopt(argc, argv, "o:O::")) != -1) {
        switch (opt) {
            case 'o':
                strcpy(output, optarg);
                break;
            case 'O':
                strcpy(output, optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s -o/O file\n", argv[0]);
                exit(1);
        }
    }
    
    printf("input = %s\n", argv[optind]);
    printf("output = %s\n", output);

    return 0;
}
