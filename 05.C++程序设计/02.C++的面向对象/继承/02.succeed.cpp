/*************************************************************************
	> File Name: 02.succeed.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Apr 2024 06:50:58 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Base {
public:
    Base(string name) : name(name) {};
    string say_name() {
        return this->name;
    }
private:
    string name;
};

class A : public Base {
public :
    A() : Base("Class_A") {};
};

class B : public Base {
public :
    B() : Base("Class_B") {};
};

class C : public Base {
public :
    C() : Base("Class_C") {};
};

void func(Base &b) {
    cout << b.say_name() << endl;
    return ;
}

int main() {
    A a;
    B b;
    C c;
    func(a);
    func(b);
    func(c);

    return 0;
}
