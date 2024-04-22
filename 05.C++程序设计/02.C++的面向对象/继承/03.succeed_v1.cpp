/*************************************************************************
	> File Name: 03.succeed_v1.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Apr 2024 07:16:08 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
//演示派生类与基类的构造与析构顺序

#define BEGINS(x) namespace x {
#define END(x) }


BEGINS(test1)

class ATTR_1 {
public :
    ATTR_1() : name("NULL") {}
    ATTR_1(string name) : name(name) {
        cout << "ATTR_1 constructor " << this->name << endl;
    }
    ~ATTR_1() {
        cout << "ATTR_1 destructor " << this->name << endl;
    }
    string name;
};

class ATTR_2 {
public :
    ATTR_2() : name("NULL") {}
    ATTR_2(string name) : name(name) {
        cout << "ATTR_2 constructor " << this->name << endl;
    }
    ~ATTR_2() {
        cout << "ATTR_2 destructor " << this->name << endl;
    }
    string name;
};


class Base {
public : 
    Base() : att1(ATTR_1()), att2(ATTR_2()) {
        cout << "Base constructor" <<  endl;
    }
    Base(string name1, string name2) : att1(ATTR_1(name1)), att2(ATTR_2(name2)) {
        cout << "Base constructor" << endl;
    }
    ~Base() {
        cout << "Base destructor" << endl;   
    }

private :
    ATTR_1 att1;
    ATTR_2 att2;
};


class A : public Base {
public :
    A() : Base() {
        cout << "A default constructor" << endl;
    }
    A(string name1, string name2) :  Base(name1, name2){
        cout << "A constructor " << endl;
    }
    ~A() {
        cout << "A destructor" << endl;
    }
};


int main() {
    //A a;
    A aa("hello", "ketty");
    return 0;
}

END(test1)


int main() {
    test1::main();
    return 0;
}
