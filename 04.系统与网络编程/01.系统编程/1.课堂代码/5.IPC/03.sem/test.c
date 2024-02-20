/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Tue 20 Feb 2024 08:14:30 PM CST
 ************************************************************************/

#include<stdio.h>

#define MAX_NUM 1000

int arr[MAX_NUM + 5][MAX_NUM + 5];

int main() {
    for (int i = 0; i < MAX_NUM; i++) {
        for (int m = 0; m < MAX_NUM; m++) {
            for (int n = 0; n < MAX_NUM; n++) {
               // arr[n][m] = 1;
                arr[m][n] = 1;
            }
        }
    }
    
    return 0;
}
