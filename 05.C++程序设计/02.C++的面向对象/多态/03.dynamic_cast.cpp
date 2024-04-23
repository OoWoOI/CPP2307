/*************************************************************************
	> File Name: 03.dynamic_cast.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 23 Apr 2024 06:02:00 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }


BEGINS(test1) 

class Base {
public :
    virtual ~Base() {}
};

class A : public Base {
public :

};

class B : public Base {
public :

};

class C : public Base {
  
public :


};

int main() {
    srand(time(0));
    Base *p;
    switch (rand() % 4) {
        case 0: p = new A(); break;
        case 1: p = new B(); break;
        case 2: p = new C(); break;
        case 3: p = nullptr; break;
    }
    A a;
    B b;
    C c;
    if (p) ((void **) (p))[0] = ((void **)(&a))[0];//修改虚函数表地址
    if (dynamic_cast<A *>(p) != nullptr) {
        cout << "p pointer A class Object" << endl;
    } else if (dynamic_cast<B *>(p) != nullptr) {

        cout << "p pointer B class Object" << endl;
    } else if (dynamic_cast<C *>(p) != nullptr) {

        cout << "p pointer C class Object" << endl;
    } else {
        cout << "p pointer nullptr" << endl;
    } 

    return 0;
}


ENDS(test1)

int main() {
    test1::main(); 
    return 0;
}
