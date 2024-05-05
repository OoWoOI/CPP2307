/*************************************************************************
	> File Name: thread_pool_v1.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 05 May 2024 11:34:05 AM CST
 ************************************************************************/

#include<iostream>
#include<functional>
#include<mutex>
#include<queue>
#include<condition_variable>
#include<thread>
using namespace std;

namespace thread_pool {

class Task {
public :
    template<typename FUNC_T, typename ...ARGS> 
    Task(FUNC_T f, ARGS ...args) {
        this->func = std::bind(f, std::forward<ARGS>(args)...);//绑定函数与参数 
    }
    void run() {
        func();//执行函数
        return ;
    }
private :
    std::function<void()> func;//函数指针
};

class Threadpool {
public :
    Threadpool(int); 
    void start();
    void stop();
    template<typename FUNC_T, typename ...ARGS>
    void add_one_task(FUNC_T, ARGS...);
    ~Threadpool() {
        this->stop();
    } 
private :
    void thread_loop();
    void __stop_set_false();
    void __add_one_task(Task *);
    Task *get_one_task();

    int __size;
    volatile bool is_started;
    std::vector<std::thread *> Threads;//线程池
    std::queue<Task *> Tasks;
    
    std::mutex m_mutex;
    std::condition_variable m_cond;
};

//线程池成员函数定义

Threadpool::Threadpool(int size = 10) : 
    __size(size),
    is_started(false),
    m_mutex(),
    m_cond()
{
    
}
template<typename FUNC_T, typename ...ARGS>
void Threadpool::add_one_task(FUNC_T func, ARGS ...args) {
    //向任务队中添加任务
    __add_one_task(new Task(func, std::forward<ARGS>(args)...));
    return ;
}

void Threadpool::__add_one_task(Task *t) {
    Tasks.push(t);;
    return ;
}



Task *Threadpool::get_one_task() {
    Task *t = nullptr;
    if (!Tasks.empty() && is_started) {
        t = Tasks.front();
        Tasks.pop();
    }
    return t;
}

void Threadpool::thread_loop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (is_started) {
        Task *t = get_one_task();
        if (t != nullptr) {
            std::cout << "thread_loop tid : " << std::this_thread::get_id() << std::endl;
            t->run();
        }
    }
    lock.unlock();
    m_cond.notify_all
    return ;
}

void Threadpool::start() {
    //开始执行任务
    is_started = true;
    for (int i = 0; i < __size; i++) {
        Threads.push_back(new std::thread(&Threadpool::thread_loop, this));
    }
    return ;
}

void Threadpool::__stop_set_false() {
    is_started = false;
    return ;
}

void Threadpool::stop() {
    //停止执行任务
    __stop_set_false();//关闭线程
    for (int i = 0; i < __size; i++) {
        Threads[i]->join();
        delete Threads[i];
    }
    Threads.clear();
}

}


bool is_prime(int x) {
    if (x <= 0) return false;
    if (x <= 3 && x >= 1) return true;
    for (int i = 2; i * i <= x; i++) {
        if (x % i) continue;
        return false;
    }
    return true;
} 

//统计50000000以内的素数个数
void prime_count(int l, int r, int &ret) {
    for (int i = l; i <= r; i++) {
        ret += is_prime(i);
    }
    return ;
}



int main() {
    #define THREAD_MAX 10
    #define OFFSET 5000000
    thread_pool::Threadpool pool(10);
    int ret[THREAD_MAX] = {0};
    for (int i = 0; i < THREAD_MAX; i++) {
        pool.add_one_task(&prime_count, i * OFFSET, (i + 1) *  OFFSET - 1, std::ref(ret[i]));
    }
    pool.start();
    pool.stop();
    int ans  = 0;
    for (int i = 0; i < THREAD_MAX; i++) ans += ret[i];
    cout << ans << endl;
    return 0;
}
