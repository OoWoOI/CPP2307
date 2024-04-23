/*************************************************************************
	> File Name: 02.stack_unwind.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 23 Apr 2024 07:38:03 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Helper { //工具人
public : 
    Helper() {cout << "helper ctor" << endl;}
    void boom() {cout << "helper boom" << endl;}
    ~Helper() {cout << "helper dtor" << endl;}
};

Helper *h;

void inner() {
   // Helper h[3];
    h = new Helper[3];
    throw (1);
    h[0].boom();
    return ;
}

void outer() {
    try {
        inner();
    } catch (int &ret){
        cout << "execption :  " << ret << endl;
    }
    delete[] h;//手动析构堆上的对象
    return ;
}

int main() {
    outer();
    return 0;//演示C++的栈解旋过程
}
