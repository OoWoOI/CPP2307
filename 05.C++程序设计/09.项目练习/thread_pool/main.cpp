/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 06 May 2024 04:16:58 PM CST
 ************************************************************************/

#include<iostream>
#include<functional>
#include"thread_pool.h"
using namespace std;

void func(int x, int &n) {
    n += 2;
    cout << "Task : " << x << " "  << n << endl;
}


bool is_prime(int x) {
    if (x < 1) return false;
    if (x <= 3 && x >= 1) return true;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false; 
    }
    return true;
}

void prime_count(int l, int r, int &ret) {
    cout << l << " " << r << endl;
    for (int i = l; i <= r; i++) {
        ret += is_prime(i);
    }
    return ;
}

int main() {
    int n = 123;
    ThreadPool::Task t(&func, 23, std::ref(n));
    t.run();
    cout << n << endl;
    //Thread_pool类
    #define THREAD_MAX 10
    #define OFFSET 5000000
    int ret[THREAD_MAX] = {0};
    ThreadPool::thread_pool pool(THREAD_MAX);
    for (int i = 0; i < THREAD_MAX; i++) {
        pool.add_one_task(&prime_count, i * OFFSET, (i + 1) * OFFSET - 1, std::ref(ret[i]));
    }
    pool.start();
    pool.stop();
    int ans = 0;
    for (int i = 0; i < THREAD_MAX; i++) ans += ret[i];
    cout << ans << endl;
    return 0;
}
