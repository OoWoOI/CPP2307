/*************************************************************************
	> File Name: thread_pool.h
	> Author: 
	> Mail: 
	> Created Time: Mon 06 May 2024 04:10:03 PM CST
 ************************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include<iostream>
#include<algorithm>
#include<functional>
#include<queue>
#include<thread>
#include<mutex>
#include<vector>
#include<condition_variable>

namespace ThreadPool {

//任务类
class Task {
public :
    template<typename FUNC_T, typename ...ARGS>
    Task(FUNC_T, ARGS...);
    void run();
    ~Task() {}
private :
    std::function<void()> func;
};

template<typename FUNC_T, typename ...ARGS>
Task::Task(FUNC_T f, ARGS ...args) {
    this->func = std::bind(f, std::forward<ARGS>(args)...); 
}

void Task::run() {
    this->func();
}

class thread_pool {
public :
    thread_pool(int size = 10);
    void start();
    template<typename FUNC_T, typename ...ARGS>
    void add_one_task(FUNC_T, ARGS...);
    void stop();
    ~thread_pool() {stop();}
private :
    
    void thread_loop();
    Task *get_one_task();
    void __add_one_task(Task *t);
 
    void __stop_set_false();
    

    int thread_size;
    bool is_started;
    std::vector<std::thread *> Threads;
    std::queue<Task *> Tasks;
    
    std::mutex m_mutex;
    std::mutex q_mutex;//队列锁
    std::condition_variable m_cond;

};


thread_pool::thread_pool(int size) :
    thread_size(size),
    is_started(false),
    m_mutex(),
    m_cond()
{
    //线程池有参构造
} 



void thread_pool::__add_one_task(Task *t) {
    std::unique_lock<std::mutex> lock(m_mutex);
    Tasks.push(t);
    m_cond.notify_one();//通知正在等待的线程
    return ;
}


template<typename FUNC_T, typename ...ARGS>
void thread_pool::add_one_task(FUNC_T f, ARGS ...args) {
    __add_one_task(new Task(f, std::forward<ARGS>(args)...));
}

Task *thread_pool::get_one_task() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (is_started && Tasks.empty()) {
        m_cond.wait(lock);//等待通知
    }
    std::cout << Tasks.size() << std::endl;
    Task *t = nullptr;
    if (!Tasks.empty()) {
        t = Tasks.front();
        Tasks.pop();
    }
    if (Tasks.empty()) m_cond.notify_all();
    return t;
}

void thread_pool::thread_loop() {
     
    while (is_started) {
        //开启
        Task *t = get_one_task();
        if (t != nullptr) {
            std::cout << "Task is run by tid = " << std::this_thread::get_id() << std::endl;
            t->run();
        }
        //防止一直请求，导致CPU密集处理需要休息200ms
        std::this_thread::sleep_for(std::chrono::microseconds(200));
    }

    return ;
}


void thread_pool::start() {
    std::unique_lock<std::mutex> lock(this->m_mutex);//获得锁
    is_started = true;
    for (int i = 0; i < thread_size; i++) {
        this->Threads.push_back(new std::thread(&thread_pool::thread_loop, this));
    }
    
    while (!Tasks.empty()) m_cond.wait(lock);

    return ;
}


void thread_pool::__stop_set_false() {
    std::unique_lock<std::mutex> lock(m_mutex);
    //获取队列锁
    is_started = false;
    m_cond.notify_all();
    return ;
}

void thread_pool::stop() {
    
    __stop_set_false();
    
    for (int i = 0; i < Threads.size(); i++) {
        Threads[i]->join();
        delete Threads[i];
    }
    Threads.clear();
    return ;
}

}


#endif
