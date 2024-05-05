/*************************************************************************
	> File Name: thread_pool.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 04 May 2024 08:24:51 AM CST
 ************************************************************************/

#include<iostream>
#include<thread>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(thread_usage)

void func() {
    cout << "hello world" << endl;
    return ;
}

void print(int a, int b) {
    cout << a << " " << b << endl;
    return ;
}


int main() {
    thread t1(func);
    t1.join();
    thread t2(print, 3, 4);
    t2.join();
    return 0;
}

ENDS(thread_usage)

#define MAX_NUM 50000000
#define THREAD_NUM 10
#define off 5000000

BEGINS(prime_count_test) 

//要求：使用10个线程实现素数个数的统计，空间复杂度要求O(1)， 数据范围0 - 50000000



bool is_prime(int n) {
    if (n <= 0) return false;
    if (n <= 3 && n >= 1) return true;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

//多线程的入口函数与功能函数要分开：高内聚低耦合

int prime_count(int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; i++) {
        ans += is_prime(i);
    }
    return ans;
}

void worker(int l, int r, int &ret) {
    cout << this_thread::get_id() << " begin" << endl;
    ret = prime_count(l, r);
    cout << this_thread::get_id() << " done" << endl;
    return ;
}


int main() {
    thread *t[THREAD_NUM];
    int ret[THREAD_NUM];
    for (int i = 0, j = 0; i < THREAD_NUM; i++, j += off) {
        t[i] = new thread(worker, j, j + off - 1, ref(ret[i]));
    }
    for (int i = 0; i < THREAD_NUM; i++) t[i]->join();
    for (int i = 0; i < THREAD_NUM; i++) delete t[i];
    int ans = 0;
    for (int i = 0; i < THREAD_NUM; i++) ans += ret[i];
    cout << ans << endl;
    return 0;
}

ENDS(prime_count_test)


#include<mutex>

std::mutex m_mutex;

BEGINS(prime_count_test1) 

//要求：使用10个线程实现素数个数的统计，空间复杂度要求O(1)， 数据范围0 - 50000000


bool is_prime(int n) {
    if (n <= 0) return false;
    if (n <= 3 && n >= 1) return true;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

//多线程的入口函数与功能函数要分开：高内聚低耦合

int ans = 0;

int prime_count(int l, int r) {
    unique_lock<mutex> lock(m_mutex);
    cout << this_thread::get_id() << " begin" << endl;
    for (int i = l; i <= r; i++) {
        ans += is_prime(i);
    }
    cout << this_thread::get_id() << " done" << endl;
    lock.unlock();
    return ans;
}


int main() {
    thread *t[THREAD_NUM];
    for (int i = 0, j = 0; i < THREAD_NUM; i++, j += off) {
        t[i] = new thread(prime_count, j, j + off - 1);
    }
    for (int i = 0; i < THREAD_NUM; i++) t[i]->join();
    for (int i = 0; i < THREAD_NUM; i++) delete t[i];
    cout << ans << endl;
    return 0;
}

ENDS(prime_count_test1)
BEGINS(prime_count_test2) 

//要求：使用10个线程实现素数个数的统计，空间复杂度要求O(1)， 数据范围0 - 50000000


bool is_prime(int n) {
    if (n <= 0) return false;
    if (n <= 3 && n >= 1) return true;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

//多线程的入口函数与功能函数要分开：高内聚低耦合

int ans = 0;

int prime_count(int l, int r) {
    cout << this_thread::get_id() << " begin" << endl;
    for (int i = l; i <= r; i++) {
        int ret = is_prime(i);
        __sync_fetch_and_add(&ans, ret);
    }
    cout << this_thread::get_id() << " done" << endl;
    return ans;
}


int main() {
    thread *t[THREAD_NUM];
    for (int i = 0, j = 0; i < THREAD_NUM; i++, j += off) {
        t[i] = new thread(prime_count, j, j + off - 1);
    }
    for (int i = 0; i < THREAD_NUM; i++) t[i]->join();
    for (int i = 0; i < THREAD_NUM; i++) delete t[i];
    cout << ans << endl;
    return 0;
}

ENDS(prime_count_test2)


#include<utility>
#include<functional>
#include<unordered_map>

BEGINS(thread_pool)

class Task {
public : 


private :

};

class Threadpool {
public :
    Threadpool(int size = 10) : __size(size){}
    template<typename FUNC_T, typename ...ARGS>
    void add_one(FUNC_T f, ARGS ...args) {
        //bind绑定函数与参数
        this->func = bind(f, std::forward<ARGS>(args)...);
        return ;
    }

    void run() {

    }

    void stop() {
        
    }

private :
    void stop_thread() {
            
    }
    int __size;
    unordered_map<decltype(this_thread::get_id()), bool> pool;
    function<void()> func;
};




bool is_prime(int n) {
    if (n <= 0) return false;
    if (n <= 3 && n >= 1) return true;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

//多线程的入口函数与功能函数要分开：高内聚低耦合

int prime_count(int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; i++) {
        ans += is_prime(i);
    }
    return ans;
}

void worker(int l, int r, int &ret) {
    cout << this_thread::get_id() << " begin" << endl;
    ret = prime_count(l, r);
    cout << this_thread::get_id() << " done" << endl;
    return ;
}





int main() {
    #define THREAD_MAX_NUM 10
    #define OFFSET 5000000
    Threadpool p(THREAD_MAX_NUM);
    int t[THREAD_MAX_NUM];
    for (int i = 0; i < THREAD_MAX_NUM; i++) {
        p.add_one(&worker, i * OFFSET, (i + 1) * OFFSET - 1, ref(t[i]));
    }
    p.run();
    p.stop();
    int ans = 0;
    for (int i = 0; i < THREAD_MAX_NUM; i++) ans += t[i];
    cout << ans << endl;
    return 0;
}

ENDS(thread_pool)


int main() {
    //thread_usage::main();
    //prime_count_test2::main();
    pthread_pool::main();
    return 0;
}
