/*************************************************************************
	> File Name: 04.IQueue.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Apr 2024 09:35:52 PM CST
 ************************************************************************/

#include<iostream>
#include<functional>
using namespace std;


#define TSTART(x) namespace x {
#define TEND(x) }

class IQueue {
public : 
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual int front() = 0;
    virtual bool full() = 0;
    virtual void expand() = 0;
    virtual ~IQueue() {} 
    
};


//普通队列
class queue : public IQueue {
public :
    queue();
    queue(int n);
    
    //队列基本操作
    bool empty() override;
    bool full() override;
    int size() override;
    int front() override;
    void push(int) override;
    void pop() override;
    void clear() override;
    void expand() override;
    void show();
    ~queue();

private :
    int capacit, head, tail, cnt;
    int *data;
};

queue::queue():capacit(10), head(0), tail(0), cnt(0) {
    this->data = new int[this->capacit];
}

queue::queue(int n) : capacit(n), head(0), tail(0), cnt(0) {
    this->data = new int[this->capacit];
}

bool queue::empty() {
    return this->cnt == 0;
}

bool queue::full() {
    return this->capacit == this->cnt; 
}

int queue::size() {
    return this->cnt;
}

void queue::expand() {
    int size = this->capacit;
    int *p = NULL;
    while (size) {
        p = new int[size + this->capacit];
        if (p) break;
        size /= 2;
    }
    if (p == NULL) return ;
    for (int i = 0; i < this->cnt; i++) {
        int ind = (this->head + i) % this->capacit;
        p[i] = this->data[ind];
        
    }
    this->head = 0;
    this->tail = this->cnt;
    this->capacit = size;
    swap(this->data, p);
    delete[] p;
    return ;
}



void queue::push(int val) {
    if (this->full()) {
        this->expand();
    }
    this->data[this->tail] = val;
    this->tail = (this->tail + 1) % this->capacit;
    this->cnt += 1;
    return ;
}

void queue::pop() {
    if (this->empty()) return ;
    this->head = (this->head + 1) % this->capacit;
    this->cnt -= 1;
    return ;
}

int queue::front() {
    if (this->empty()) return -1;
    return this->data[this->head];//返回队首元素
}


void queue::clear() {
    this->cnt = 0;
    this->head = this->tail = 0;
    return ;
}

queue::~queue() {
    delete[] this->data;
    return ;
}

void queue::show() {
    cout << "【size : " << this->capacit << " : " << this->size() << "】 " ; 

    for (int i = 0; i < this->cnt; i++) {
        i && cout << " ";
        int ind = (this->head + i) % this->capacit;
        cout << this->data[ind];
    }
    cout << endl;
    return ;
}

//优先队列

class priority_queue : public IQueue {
public :
    priority_queue();
    priority_queue(int, function<bool(int, int)>);//自定义排序规则
    bool empty() override;
    bool full() override;
    int size() override;
    int front() override;
    void push(int) override;
    void pop() override;
    void clear() override;
    void expand() override;
    void down_update(int);
    void update();
    void destroy();
    void show();
    ~priority_queue();
private : 
    int capacit, head, tail, cnt;
    function<bool(int, int)> cmp;
    int *data;
};


priority_queue::priority_queue() 
    : capacit(11), cnt(0) , cmp(less<int>()){
    this->data = new int[this->capacit];
}

priority_queue::priority_queue
    (int n, function<bool(int, int)> cmp = less<int>()) 
    : capacit(n + 1), cnt(0), cmp(cmp) {
    this->data = new int[this->capacit];
}

priority_queue::~priority_queue() {
    delete[] this->data;
}

bool priority_queue::full() {
    return this->cnt == this->capacit;//空间不足
}

bool priority_queue::empty() {
    return this->cnt == 0;
}

void priority_queue::expand() {
    int size = this->capacit;
    int *p = NULL;
    while (size) {
        p = new int[this->capacit + size + 1];
        if (p) break;
        size /= 2;
    }
    if (p == NULL) return ;
    for (int i = 1; i <= this->cnt; i++) {
        p[i] = this->data[i];
    }
    this->capacit += size;
    swap(this->data, p);
    delete[] p;
    return ;
}

int priority_queue::size() {
    return this->cnt;
}

int priority_queue::front() {
    if (this->cnt == 0) return -1;
    return this->data[1];
}

void priority_queue::down_update(int i) {
    while (i * 2 <= this->cnt) {
        int ind = i, l = i * 2, r = i * 2 + 1;
        if (l <= this->cnt && this->cmp(this->data[l], this->data[ind])) ind = l;
        if (r <= this->cnt && this->cmp(this->data[r], this->data[ind])) ind = r;
        if (ind == i) break;
        swap(this->data[ind], this->data[i]);
        i = ind;
    }
    return ;
}

void priority_queue::update() {
    for (int i = this->cnt / 2; i >= 1; i--) {
        down_update(i);
    }
    return ;
}

void priority_queue::push(int val) {
    if (this->full()) {
        this->expand();//空间不足，扩容
    }
    //尾部入堆
    this->data[++this->cnt] = val;
    this->update();//调整
    return ;
}

void priority_queue::pop() {
    if (this->empty()) return ;
    //堆顶元素出堆
    swap(this->data[1], this->data[this->cnt]);
    this->cnt -= 1;
    this->update();
    return ;
}

void priority_queue::clear() {
    if (this->data == NULL) return ;
    this->cnt = 0;
    return ;
}

void priority_queue::destroy() {
    if (this->data == NULL) return ;
    free(this->data);
    return ;
}

void priority_queue::show() {
    cout << "[" << this->capacit << ":" << this->cnt << "] ";
    for (int i = 1; i <= this->cnt; i++) {
        if (i != 1) cout << " ";
        cout << this->data[i];
    }
    cout << endl;
    return ;
}

class CMP {
public :
    bool operator>(int b) {
        return this->a > b;
    }
    int a;
};

TSTART(test1)

int main() { 
    //测试普通队列
    #define MAX_NUM 10
    queue q(MAX_NUM);
    srand(time(0));
    int opt;
    cout << "【 0 】 插入元素" << endl;
    cout << "【 1 】 弹出元素" << endl;
    cout << "【 2 】 队首元素" << endl;
    cout << "【 3 】 清空元素" << endl;
    while (cin >> opt) {
        switch (opt) {
            case 0: {
                //插入元素
                int val;
                cin >> val;
                q.push(val);
            } break;
            case 1: {
                //弹出元素
                q.pop();
            } break;
            case 2: {
                //获取头部元素
                cout << q.front() << endl;
            } break;
            case 3: {
                //清空元素
                q.clear();
            } break;
            default :
                break;
        }
        q.show();
    }
    return 0;
}

TEND(test1)

TSTART(test2)



int main() {
    //测试优先队列
    int opt, val;
    cout << "0 : 插入元素" << endl;
    cout << "1 : 删除元素" << endl;
    cout << "2 : 清空队列" << endl;
    priority_queue q(10, [&](int a, int b){
        return a > b;
    });
    while (cin >> opt) {
        switch (opt) {
            case 0: {
                cin >> val;
                q.push(val);
            } break;
        case 1: {
                q.pop();
            } break;
        case 2: {
                q.clear();
            } break;
        }
        q.show();
    }
    
    return 0;
}

TEND(test2)


int main() {
    test2::main();
    
    return 0;
}

