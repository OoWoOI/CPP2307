/*************************************************************************
	> File Name: 01.Animal.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 23 Apr 2024 03:46:06 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define END(x) }


BEGINS(test1)
class Animal {
public :
    void run() {
        cout << "I don't know how to run " << endl;
        return ;
    }
};

class Cat : public Animal {
public :
    void run() {
        cout << "I can run with four legs" << endl;
        return ;
    }
};

int main() {
    Cat a;
    Animal &b = a;
    Animal *c = &a;
    a.run();
    b.run();
    c->run();
    return 0;
}
END(test1)


BEGINS(test2)
class Animal {
public :
    virtual void run() {
        cout << "I don't know how to run " << endl;
        return ;
    }
};

class Cat : public Animal {
public :
    void run() override {
        cout << "I can run with four legs" << endl;
        return ;
    }
};

int main() {
    Cat a;
    Animal &b = a;
    Animal *c = &a;
    a.run();
    b.run();
    c->run();
    return 0;
}
END(test2)

BEGINS(test3)
class Animal {
public :
    virtual void run() {
        cout << "I don't know how to run " << endl;
        return ;
    }
    virtual ~Animal() {
        cout << "Animal destructor" << endl; 
    }
};

class Cat : public Animal {
public :
    void run() override {
        cout << "I can run with four legs" << endl;
        return ;
    }
    ~Cat() {
        cout << "Cat destructor" << endl;
        
    }
};
class People : public Animal {
public :
    void run() override {
        cout << "I can run with two legs" << endl;
        return ;
    }
    ~People() {
        cout << "People destructor" << endl;
    }
};
class Bird : public Animal {
public :
    void run() override {
        cout << "I fly ~" << endl;
    }
    ~Bird() {
        cout << "Bird destructor" << endl;
    }
};

int main() {
    Animal *p;
    srand(time(0));
    switch (rand() % 3) {
        case 0: p = new Cat(); break;
        case 1: p = new People(); break;
        case 2: p = new Bird(); break;
        default :
            break;
    }
    p->run();
    delete p;
    return 0;
}
END(test3)



int main() {
    test3::main();
    return 0;
}
