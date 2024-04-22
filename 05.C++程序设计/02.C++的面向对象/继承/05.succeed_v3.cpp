/*************************************************************************
	> File Name: 05.succeed_v3.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Apr 2024 09:34:52 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define END(x) }

BEGINS(test1)

class A {
public : 
    int x;
};
    
class B : virtual public A{
public :
    void setX(int val) {
        this->x = val;
        cout << "setX : " << &(this->x) << endl;
        return ;
    }
};


class C : virtual public A {
public :
    int getX() {
        cout << "getX : " << &(this->x) << endl; 
        return this->x;
    }

};

class D : public B, public C {
public :
    
};

int main() {
    D d;
    d.setX(120);
    cout << d.getX() << endl;

    d.setX(110);
    cout << d.getX() << endl;
    return 0;
}

END(test1)

BEGINS(test2)

class NoObj {
public :
    NoObj() = delete;
    NoObj(const NoObj &a) = delete;
};



int main() {
    
    return 0;
}

END(test2)


BEGINS(test3)

class UNCOPYABLE {//标记了类的某一种性质

public :
    UNCOPYABLE(const UNCOPYABLE &) = delete;
    UNCOPYABLE &operator=(const UNCOPYABLE &) = delete;
    UNCOPYABLE &operator=(const UNCOPYABLE &) const = delete;
protected: 
    UNCOPYABLE() = default;
};

class A : public UNCOPYABLE{
};

int main() {
    A a;
    A b;
    //a = b;//NO 删除了基类的赋值
    //A c(a);//NO 删除了基类的拷贝构造
    return 0;
}

END(test3)


BEGINS(test4) 

//功能类
class HAS_XY {
public :
    int x, y;
};

class HAS_XYZ : public HAS_XY {
public :
    int z;
};

class A : public HAS_XY {
public :
    A() {x = y = 1;};
};
class B : public HAS_XYZ {
public :
    B() {x = y = z = 2;};
};
class C : public HAS_XY {
public :
    C() {x = y = 3;};
};
class D : public HAS_XYZ {
public :
    D() {x = y = z = 4;};
};
class E : public HAS_XY {
public :
    E() {x = y = 5;};
};


void func(HAS_XY &a) {
    cout << "HAS_XY : "; 
    cout << a.x << " " << a.y << endl; 
    return ;
}

void func(HAS_XYZ &a) {
    cout << "HAS_XYZ : ";
    cout << a.x << " " << a.y << " " << a.z << endl;
    return ;
}



int main() {
    A a;
    B b;
    C c;
    D d;
    E e;
    func(a);
    func(b);
    func(c);
    func(d);
    func(e);

    return 0;
}


END(test4)

int main() {
    
    test4::main(); 
    return 0;
}
