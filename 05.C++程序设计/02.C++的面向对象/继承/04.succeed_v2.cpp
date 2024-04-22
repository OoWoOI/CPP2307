/*************************************************************************
	> File Name: 04.succeed_v2.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Apr 2024 07:45:09 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;



//继承中的拷贝行为
class ATTR_1 {
public : 
    ATTR_1(string name) : name(name) {
        cout << "ATTR_1 constructor : " << this->name << endl; 
    }
    //拷贝构造
    ATTR_1(const ATTR_1 &a) : name(a.name) {
        cout << "ATTR_1 copy constructor : " << this->name << endl;
    };
    ATTR_1 &operator=(const ATTR_1 &a) {
        this->name = a.name;
        cout << "ATTR_1 operator= copy " << this->name << endl;
        return *this;
    }
    ~ATTR_1(){
        cout << "ATTR_1 destructor : " <<  this->name << endl;
    }
    string name;
};

class ATTR_2 {
public : 
    ATTR_2(string name) : name(name) {
        cout << "ATTR_2 constructor : " << this->name << endl; 
    }
    //拷贝构造
    ATTR_2(const ATTR_2 &a) : name(a.name) {
        cout << "ATTR_2 copy constructor : " << this->name << endl;
    };
    ATTR_2 &operator=(const ATTR_2 &a) {
        this->name = a.name;
        cout << "ATTR_2 operator= copy " << this->name << endl;
        return *this;
    }
    ~ATTR_2(){
        cout << "ATTR_2 destructor : " <<  this->name << endl;
    }
    string name;
};

class Base {

public : 
    Base() : att1(ATTR_1("none")), att2(ATTR_2("none")) {
        cout << "Base default constructor" << endl;
    };
    Base(string name1, string name2) : att1(ATTR_1(name1)), att2(ATTR_2(name2)) {
        cout << "Base constructor" << endl;
    }
    
    Base &operator=(const Base &b) {
        cout << "Base operator= copy" <<endl;
        this->att1 = b.att1;
        this->att2 = b.att2;
        return *this;
    }

    Base(const Base &b) : att1(ATTR_1(b.att1)), att2(ATTR_2(b.att2)) {
        cout << "Base copy constructor" << endl;
    };
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
    }; 
    A(string name1, string name2) : Base(name1, name2){
        cout << "A constructor" << endl;
    };
    A &operator=(const A &b) {
        cout << "A operator= copy" << endl;
        this->Base::operator=(b);
        return *this;
    } 
    A(const A &a) : Base(a) {
        cout << "A copy constructor" << endl;
    };

    ~A() {
      cout << "A destructor" << endl;  
    };
};

int main() {
    cout << " ============== copy constructor ================= " << endl << endl;
    A a("hello", "ketty");
    A b(a);
    cout << " ============== assign constructor ================= " << endl << endl;
    A c;
    c = b;
    cout << " ============== END constructor ================= " << endl << endl;
    return 0;
}
