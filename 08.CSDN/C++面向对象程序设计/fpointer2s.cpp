/*************************************************************************
	> File Name: fpointer2s.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 05 May 2024 08:16:02 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Base {
public :
    virtual void print() = 0;
    virtual ~Base() {};
};

class Derived : public Base {
public :
    void print() override {
        cout << "this Derived" << endl;
    }
    ~Derived() {}
};


int main() {
    Base *ptr = new Derived();
    ptr->print();
    return 0;
}
