/*************************************************************************
	> File Name: 05.template_args.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 01 May 2024 09:38:18 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1) 

class A {
public :
    A(int x, int y) : x(x), y(y) {}
    int x,  y;
};

ostream &operator<<(ostream &out, A &a) {
    out << "class A : " << a.x << " " <<  a.y;
    return out;
}

template<class T>
void print(T a) {
    cout << a << endl;
    return ;
}

template<class T, class ...ARGS>
void print(T &a, ARGS... args) {
    cout << a << endl;
    print(args...);
    return ;
}

int main() {
    A a(2, 4);
    print("hello word");
    print("hello word", a, 1, 2.5);
    print(a, 1, 1.2);
    return 0;
}

ENDS(test1)


BEGINS(test2)

template<class T, class ...ARGS>
class ARG{
public :
    typedef T type;
    typedef ARG<ARGS...> rest;
};

template<class T>
class ARG<T>{//模板偏特化
public :
    typedef T type;
};


template<typename T, typename ...ARGS>
class Test {
public :
    T operator()(typename ARG<ARGS...>::type a, typename ARG<ARGS...>::rest::type b) {
        return a + b;
    }
};


int main() {
    Test<int, int, int> t1;
    Test<double, double, int> t2;
    cout << t1(3, 4) << endl;
    cout << t2(3.5, 4) << endl;
    return 0;
}

ENDS(test2)

BEGINS(test3)

template<class T, class ...ARGS>
class ARG{
public :
    typedef T type;
    typedef ARG<ARGS...> rest;
};

template<class T>
class ARG<T>{//模板偏特化
public :
    typedef T type;
    typedef T ftype;
};


template<typename T, typename ...ARGS>
class Test {
public :
    T operator()(typename ARG<ARGS...>::type a, typename ARG<ARGS...>::rest::ftype b) {
        return a + b;
    }
};


int main() {
    Test<int, int, int> t1;
    Test<double, double, int> t2;
    //Test<double, double, int, int> t3;//当参数数量匹配不报错，否则报错
    cout << t1(3, 4) << endl;
    cout << t2(3.5, 4) << endl;
    //cout << t3(3.5, 4, 12) << endl;
    return 0;
}

ENDS(test3)
BEGINS(test4)

template<class T, class ...ARGS>
class ARG{
public :
    typedef T type;
    typedef ARG<ARGS...> rest;
};

template<class T>
class ARG<T>{//模板偏特化
public :
    typedef T type;
};

template<typename T, typename ...ARGS> class Test;
template<typename T, typename ...ARGS>
class Test<T(ARGS...)> {
public :
    T operator()(typename ARG<ARGS...>::type a, typename ARG<ARGS...>::rest::type b) {
        return a + b;
    }
};


int main() {
    Test<int(int, int)> t1;
    Test<double(double, int)> t2;
    cout << t1(3, 4) << endl;
    cout << t2(3.5, 4) << endl;
    return 0;
}

ENDS(test4)


BEGINS(test5)



template<int M>
void print() {
    cout << M << ", ";
    print<M - 1>();
    return ;
}

template<>
void print<1>() {
    cout << "1" << endl;
    return ;
}

int main() { 
    print<20>();
    print<10>();
    print<5>();
    print<3>();
    return 0;
}

ENDS(test5)

BEGINS(test6)

template<int N, typename T, typename ...ARGS>
class ARG {
public :
    typedef typename ARG<N - 1, ARGS...>::type type;
};



template<typename T, typename ...ARGS>//模板偏特化
class ARG<1, T, ARGS...>{
public :
    typedef T type;
};


template<typename T>//模板偏特化
class ARG<1, T>{
public :
    typedef T type;
};


template<typename T, typename ...ARGS>
class NUM_ARGS {
public :
    static constexpr int r = NUM_ARGS<ARGS...>::r + 1;
};

template<typename T>
class NUM_ARGS<T> {
public :
    static constexpr int r = 1;
};

template<int N>
class Zero {
public :
    typedef int no;
};

template<>
class Zero<0> {
public :
    typedef int yes;
};

template<typename T, typename ...ARGS> class Test;
template<typename T, typename ...ARGS>
class Test<T(ARGS...)>{
public :
    typedef typename Zero<2 - NUM_ARGS<ARGS...>::r>::yes TYPE_NUM_2; 
    T operator()(
        typename ARG<1, ARGS...>::type a,
        typename ARG<2, ARGS...>::type b) {
        return a + b;
    }
};

int main() {
    Test<bool(int, int)> t1;
    cout << t1(1, 2) << endl;
    cout << t1(3, 4) << endl;
    return 0;
}

ENDS(test6)

int main() {
    test6::main();
    return 0;
}
