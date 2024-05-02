/*************************************************************************
	> File Name: 07.function.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 02 May 2024 06:52:57 PM CST
 ************************************************************************/

#include<iostream>
#include<functional>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(reference_param)

template<typename T>
struct remove_reference {
    typedef T type;
};

template<typename T>
struct remove_reference<T&> {
    typedef T type;
};

template<typename T>
struct remove_reference<T&&> {
    typedef T type;
};

template<typename T>
void func(T &&a) {
    typename remove_reference<T>::type c;
    cout << "function T& a = " << a << endl;
    return ;
}

int main() { 
    int n = 123;
    func(n);
    func(123);
    typename remove_reference<int &&>::type a;
    typename remove_reference<int &>::type b;
    typename remove_reference<int>::type c;
    return 0;
}

ENDS(reference_param)

BEGINS(add_const) 

template<typename T>
class add_const {
public :
    typedef const T type;
};

template<typename T>
class add_const<const T> {
public :
    typedef const T type;
};


int main() {
    return 0;
}

ENDS(add_const)


BEGINS(add_l_r)
//实现添加左值引用模板类
template<typename T>
class add_lvalue_reference {
public :
    typedef T & type;
};
template<typename T>
class add_lvalue_reference<T&> {
public :
    typedef T & type;
};
template<typename T>
class add_lvalue_reference<T&&> {
public :
    typedef T & type;
};

template<typename T>
class remove_pointer {
public :
    typedef T type;
};

template<typename T>
class remove_pointer<T *> {
public :
    typedef typename remove_pointer<T>::type type;//递归去指针
};

int main() {
    cout << sizeof(remove_pointer<int>::type) << endl; 
    cout << sizeof(remove_pointer<int *>::type) << endl; 
    cout << sizeof(remove_pointer<int **>::type) << endl; 
    cout << sizeof(remove_pointer<int ***>::type) << endl; 
    return 0;
}


ENDS(add_l_r)

BEGINS(bind_usage)
int add(int a, int b) { 
    return a + b;
}

void add_one(int &a) {
    a += 1;
    return ;
}

void func(string str1, string str2) {
    cout << str1 << " " << str2 << endl;
    return ;
}

int main() {
    auto f1 = bind(add, 3, 4);//作用：打包函数与参数
    cout << f1() << endl;  
    cout << f1() << endl;  
    cout << f1() << endl;
    int a = 1;
    //auto f2 = bind(add_one, a);//传入参数a，但是最终没有修改a的值。
    auto f2 = bind(add_one, ref(a));//ref()表示此处传引用
    f2();
    f2();
    f2();
    cout << a << endl;
    func("hello", "word");
    auto f3 = bind(func, std::placeholders::_2, std::placeholders::_1);
    f3("word", "hello");
    return 0;
}

ENDS(bind_usage)


BEGINS(function_implate)

template<typename T, typename ...ARGS> class function;
template<typename T, typename ...ARGS>
class function<T(ARGS...)> {
public :
    
};

int main() {
    
    return 0;
}

ENDS(function_implate)

int main() {
   // bind_usage::main(); 
    function_implate::main();//自己实现function模板类
    return 0;
}
