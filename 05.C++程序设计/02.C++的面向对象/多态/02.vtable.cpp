/*************************************************************************
	> File Name: 02.vtable.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 23 Apr 2024 04:54:55 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define END(x) }

BEGINS(test1)
class Base {
public :
    virtual ~Base() {};
};

class A  : public Base {
public :
    int a;
};

class B {
public :
    int a;
};

int main() {
    cout << sizeof(Base) << endl;
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    return 0;
}

END(test1)

BEGINS(test2)
class Base {
public :
    virtual void func1() {cout << "Base func1" << endl;};
    virtual void func2() {cout << "Base func2" << endl;};
    virtual void func3() {cout << "Base func3" << endl;};
    virtual ~Base() {};
};

class A  : public Base {
public :
    void func2() override {
        cout << "A func 2" << endl;
        return ;
    };
    int a;
};

class B : public Base{
public :
    void func1() override {
        cout << "B func1" << endl; 
    }
    void func3() override {
        cout << "B func3" << endl;
    }
    int a;
};

typedef void (*func)();

int main() {
    A a;
    B b;
    a.func1();
    a.func2();
    a.func3();
    b.func1();
    b.func2();
    b.func3();
    //验证虚函数表的内容
    cout << "==============" << endl;
    ((func **)(&a))[0][0]();
    ((func **)(&a))[0][1]();
    ((func **)(&a))[0][2]();
    //交换两个对象所指向的虚函数表地址
    cout << "=============" << endl;
    swap(((func **)(&a))[0], ((func **)(&b))[0]);
    ((func **)(&a))[0][0]();
    ((func **)(&a))[0][1]();
    ((func **)(&a))[0][2]();
    return 0;
}

END(test2)



BEGINS(test3)
class Base {
public :
    virtual void func(int x) {
        cout << this << " class B " << x << endl;
        return ;
    }
    virtual ~Base() {}
};

class A  : public Base {
public :
    void func(int x) override {
        cout << this << " class A " << x << endl;
        return ;
    };
    int a;
};


typedef void (*func)(void *, int);

int main() {
    A a;
    //((func **)(&a))[0][0](123);//NO, this指针是隐藏参数
    ((func **)(&a))[0][0](&a, 123);
    return 0;
}

END(test3)



int main() {
    test3::main();
    return 0;
}
