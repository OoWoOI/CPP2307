/*************************************************************************
	> File Name: 01.file.c
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Jan 2024 09:29:24 PM CST
 ************************************************************************/

#include "./common/head.h"
int main(int argc, char **argv) {
    int opt;
    if (argc< 2) {
        fprintf(stderr, "Usage : %s -p file\n", argv[0]);
        exit(1);
    }

    char output[20] = {0};
    
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                strcpy(output, optarg);
                break;
            default:
                 fprintf(stderr, "Usage : %s -p file\n", argv[0]);
                exit(1);
        }
    }

    printf("input file = %s\n", argv[optind]);
    printf("output = %s\n", output);

    return 0;
}
