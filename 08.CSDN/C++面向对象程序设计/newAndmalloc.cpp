/*************************************************************************
	> File Name: newAndmalloc.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 05 May 2024 10:48:24 PM CST
 ************************************************************************/

#include <iostream>
#include <cstdlib> // 包含 malloc 函数所需的头文件

using namespace std;

class MyClass {
public:
    MyClass() {
        cout << "Constructor called" << endl;
    }
    ~MyClass() {
        cout << "Destructor called" << endl;
    }
};

int main() {
    // 使用 new 分配内存
    MyClass* ptr_new = new MyClass; // 分配一个 MyClass 对象的内存空间，并调用构造函数进行初始化
    delete ptr_new; // 释放内存空间，并调用析构函数进行清理

    // 使用 malloc 分配内存
    MyClass* ptr_malloc = (MyClass*)malloc(sizeof(MyClass)); // 使用 malloc 分配内存
    cout << "free" << endl;
    free(ptr_malloc); // 释放内存空间，注意需要使用 free 函数

    return 0;
}
