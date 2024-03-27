/*************************************************************************
	> File Name: 232.用栈实现队列.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 13 Mar 2024 06:04:57 PM CST
 ************************************************************************/

#include<iostream>
#include<stack>
using namespace std;

class MyQueue {
public:
    MyQueue() {
        s1 = new stack<int>;
        s2 = new stack<int>;
    }
    
    void push(int x) {
        stack<int> *t1 = s1->empty() ? s1 : s2;
        stack<int> *t2 = s1->empty() ? s2 : s1;
        while (!t2->empty()) {
            int tmp = t2->top();
            t1->push(tmp);
            t2->pop();
        }
        t2->push(x);
        while (!t1->empty()) {
            int tmp = t1->top();
            t2->push(tmp);
            t1->pop();
        }
        return ;
    }
    
    int pop() {
        stack<int> *t1 = s1->empty() ? s2 : s1;
        int temp = t1->top();
        t1->pop();
        return temp;
    }
    
    int peek() {
        return s1->empty() ? s2->top() : s1->top();
    }
    
    bool empty() {
        return s1->empty() && s2->empty();
    }
private :
    stack<int> *s1, *s2;
};



int main() {


    return 0;
}
