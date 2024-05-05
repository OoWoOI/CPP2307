#include <iostream>
#include <functional>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>
#include <algorithm>
#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>

namespace haizei {

class Task {
public :
    template<typename Func_T, typename ...ARGS>
    Task(Func_T f, ARGS ...args) {
        func = std::bind(f, std::forward<ARGS>(args)...);
    }
    void run() {
        func();
    }
private:
    std::function<void()> func;
};

class thread_pool {
public:        
    thread_pool(int thread_size = 5) 
    : thread_size(thread_size),
      is_started(false),
      m_mutex(),
      m_cond()
    {}
    void start();
    void stop();
    template<typename Func_T, typename ...ARGS>
    void add_one_task(Func_T f, ARGS...args) {
        __add_one_task(new Task(f, std::forward<ARGS>(args)...));
    }
    ~thread_pool() { stop(); }

private:
    void thread_loop();
    Task *get_one_task();
    void __add_one_task(Task *);
    void __stop_set_false();

    int thread_size;
    volatile bool is_started;
    std::vector<std::thread *> Threads;
    std::queue<Task *> Tasks;

    std::mutex m_mutex;
    std::condition_variable m_cond;
};

void thread_pool::start() {
    std::unique_lock<std::mutex> lock(m_mutex);
    is_started = true;
    for (int i = 0; i < thread_size; i++) {
        Threads.push_back(new std::thread(&thread_pool::thread_loop, this));
    }
}

void thread_pool::__stop_set_false() {
    std::unique_lock<std::mutex> lock(m_mutex);
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

void thread_pool::thread_loop() {
    while (is_started) {
        Task *t = get_one_task();
        if (t != nullptr) {
            std::cout << "thread_loop tid : " << std::this_thread::get_id() << std::endl;
            t->run();
        } 
    }
    return ;
}

Task* thread_pool::get_one_task() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (Tasks.empty() && is_started) {
        m_cond.wait(lock);
    }
    Task *t = nullptr;
    if (!Tasks.empty() && is_started) {
        t = Tasks.front();
        Tasks.pop();
    }
    return t;
}

void thread_pool::__add_one_task(Task *t) {
    std::unique_lock<std::mutex> lock(m_mutex);
    Tasks.push(t);
    m_cond.notify_one();
    return ;
}

}

bool is_prime(int x) {
    if (x <= 3 && x >= 1) return true;
    for (int i = 2; i * i <= x; i++) {
        if (x % i) continue;
        return false;
    }
    return true;
} 

// 统计 [l, r] 范围内的素数个数
void prime_count(int l, int r, int &ret) {
    for (int i = l; i <= r; i++) {
        ret += is_prime(i);
    }
}

int main() {
    constexpr int THREAD_MAX = 10;
    constexpr int OFFSET = 5000000;

    haizei::thread_pool pool(THREAD_MAX);
    int ret[THREAD_MAX] = {0};

    for (int i = 0; i < THREAD_MAX; i++) {
        pool.add_one_task(&prime_count, i * OFFSET, (i + 1) * OFFSET - 1, std::ref(ret[i]));
    }

    pool.start();
    pool.stop();

    int ans = 0;
    for (int i = 0; i < THREAD_MAX; i++) {
        ans += ret[i];
    }

    std::cout << ans << std::endl;
    return 0;
}

