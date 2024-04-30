/*************************************************************************
	> File Name: 04.specialization.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 30 Apr 2024 08:28:37 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }


BEGINS(test1) 

template<class T>
T add(T a, T b) {
    return a + b;
}

template<>
int add<int>(int a, int b) {
    cout << "int template" << endl;
    return a + b;
}

int main() {
    cout << add(3, 4) << endl;
    cout << add(3.2, 4.3) << endl;

    return 0;
}

ENDS(test1)

BEGINS(test2) 

template<typename T, typename U> 
class Test {
public :
    Test() {
        cout << "normal template" << endl;
    }
};


template<>
class Test<int, double> {
public :
    Test() {
        cout << "full special" << endl;
    }
};

template<typename T>
class Test<int , T> {
public :
    Test() {
        cout << "part special" << endl;
    }
};

int main() {
    Test<int, double> t1;
    Test<int, string> t2;
    Test<string, int> t3;
    return 0;
}

ENDS(test2)


BEGINS(test3)

class A {
public :
};

class B {
public :
};

template<class T>
class type_trais {
public :
    static const char *has_constructor;
};

template<class T>
const char *type_trais<T>::has_constructor = "yes";


template<class T>
class type_trais<T*> {
public :
    static const char *has_constructor;
};

template<class T>
const char *type_trais<T*>::has_constructor = "no";


template<>
class type_trais<int> {
public :
    static const char *has_constructor;
};  

const char *type_trais<int>::has_constructor = "no";

template<>
class type_trais<double> {
public :
    static const char *has_constructor;
};

const char *type_trais<double>::has_constructor = "no";

int main() {
    //判断类型是否具有默认构造函数
    cout << type_trais<int>::has_constructor << endl;//no
    cout << type_trais<A>::has_constructor << endl;//yes
    cout << type_trais<double>::has_constructor << endl;//no
    cout << type_trais<B>::has_constructor << endl;//yes
    cout << type_trais<string *>::has_constructor << endl;//no
    
    return 0;
}

ENDS(test3)



BEGINS(test4)

class yes_constructor {
public :
    static const char *has_constructor;
};
const char *yes_constructor::has_constructor = "yes";

class no_constructor {
public :
    static const char *has_constructor;
};
const char *no_constructor::has_constructor = "no";

class A {
public :
};

class B {
public :
};

template<class T>
class type_trais : public yes_constructor {};

template<class T>
class type_trais<T*> : public no_constructor {};

template<>
class type_trais<int> : public no_constructor {};  

template<>
class type_trais<double> : public no_constructor{};


int main() {
    //判断类型是否具有默认构造函数
    cout << type_trais<int>::has_constructor << endl;//no
    cout << type_trais<A>::has_constructor << endl;//yes
    cout << type_trais<double>::has_constructor << endl;//no
    cout << type_trais<B>::has_constructor << endl;//yes
    cout << type_trais<string *>::has_constructor << endl;//no
    
    return 0;
}

ENDS(test4)

BEGINS(test5)


class A {};
class B {};


class yes_constructor {};
class no_constructor{};

template<class T>
class type_trais {
public :
    typedef yes_constructor has_constructor;
};

template<>
class type_trais<int> {
public :
    typedef no_constructor has_constructor;
};

template<>
class type_trais<double> {
public :
    typedef no_constructor has_constructor;
};

template<class T>
class type_trais<T *> {
public :
    typedef no_constructor has_constructor;
};

ostream &operator<<(ostream &out, const yes_constructor  &) {
    out << "yes";
    return out;
}    

ostream &operator<<(ostream &out, const no_constructor  &) {
    out << "no";
    return out;
}

int main() {
    //判断类型是否具有默认构造函数
    cout << type_trais<int>::has_constructor() << endl;//no
    cout << type_trais<A>::has_constructor() << endl;//yes
    cout << type_trais<double>::has_constructor() << endl;//no
    cout << type_trais<B>::has_constructor() << endl;//yes
    cout << type_trais<string *>::has_constructor() << endl;//no
    return 0;
}

ENDS(test5)


int main() {
    test5::main();
    return 0;
}
