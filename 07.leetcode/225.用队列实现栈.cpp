/*************************************************************************
	> File Name: 225.用队列实现栈.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 13 Mar 2024 05:29:26 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;

class MyStack {
public :
    MyStack() {
        q1 = new queue<int>;
        q2 = new queue<int>;
    };
    
    void push(int x) {
        queue<int> *t1 = q1->empty() ? q1 : q2;
        queue<int> *t2 = q1->empty() ? q2 : q1;
        t1->push(x);
        while (!t2->empty()) {
            int tmp = t2->front();
            t1->push(tmp);
            t2->pop();
        }
        return ;
    }

    int pop() {
        queue<int> *t1 = q1->empty() ? q2 : q1;
        int tmp = t1->front();
        t1->pop();
        return tmp;
    };

    int top() {
        return q1->empty() ? q2->front() : q1->front();
    };

    bool empty() {
        return q1->empty() && q2->empty();
    };
private :
    queue<int> *q1, *q2;//队列指针
};

int main() {

    

    return 0;
}
