/*************************************************************************
	> File Name: test1.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 03 May 2024 11:57:28 PM CST
 ************************************************************************/
#include <iostream>
#include <utility>
#include <stdexcept>
using namespace std;

template<typename T, typename ...ARGS> 
class Base {
public :
    virtual T run(ARGS...) = 0;
    virtual Base<T, ARGS...> *getCopy() = 0;
    virtual ~Base() = default;
};

template<typename T, typename ...ARGS>
class normal_func : public Base<T, ARGS...> {
public :
    normal_func(T (*ptr)(ARGS...)) : func(ptr) {}
    normal_func(normal_func &obj) : func(obj.func) {}
    T run(ARGS ...args) override {
        return this->func(std::forward<ARGS>(args)...);
    }
    
    Base<T, ARGS...> *getCopy() override {
        return new normal_func(*this);
    }

    ~normal_func() {
        this->func = nullptr;    
    }
private :
    T (*func)(ARGS...);
};


template<typename CLASS_T, typename T, typename ...ARGS>
class functor : public Base<T, ARGS...> {
public :
    functor(const CLASS_T &obj) : obj(obj) {}
    functor(const functor &ft) : obj(ft.obj) {} 
    
    T run(ARGS... args) override {
        return obj(std::forward<ARGS>(args)...);
    }

    Base<T, ARGS...> *getCopy() override {
        return new functor(*this);
    }

    ~functor() {}

private :
    CLASS_T obj;
};

template<typename T, typename ...ARGS> 
class functor<std::nullptr_t, T, ARGS...> : public Base<T, ARGS...> {
public:
    functor(std::nullptr_t) {}
    
    T run(ARGS...) override {
        throw std::runtime_error("Trying to call nullptr");
    }

    Base<T, ARGS...> *getCopy() override {
        return new functor(nullptr);
    }

    ~functor() {}
};

template<typename T, typename ...ARGS> 
class function;

template<typename T, typename ...ARGS>
class function<T(ARGS...)> {
public :
    function() : obj(nullptr) {}
    function(T (*func)(ARGS...)) : obj(new normal_func<T, ARGS...>(func)) {}
    template<typename CLASS_T>
    function(CLASS_T cl) : obj(new functor<CLASS_T, T, ARGS...>(cl)) {}

    //重载=
    function &operator=(T (*func)(ARGS...)) {
        delete this->obj;
        this->obj = new normal_func<T, ARGS...>(func);
        return *this;
    }
    template<typename CLASS_T>
    function &operator=(const CLASS_T &obj) {
        delete this->obj;
        this->obj = new functor<CLASS_T, T, ARGS...>(obj);
        return *this;
    }

    function &operator=(const function<T(ARGS...)> &ft) {
        delete this->obj;
        this->obj = ft.obj->getCopy();
        return *this;
    }
    
    //重载()
    T operator()(ARGS ...args) {
        return obj->run(std::forward<ARGS>(args)...);
    }

    //重载bool
    operator bool() {
        return this->obj != nullptr;
    }

    ~function() {
        delete this->obj;
    }
private :
    Base<T, ARGS...> *obj;
};


int add(int a, int b) {
    cout << "normal_func" << endl;
    return a + b;
}

class Foo {
public :
    Foo(int x = 0) : x(x) {}
    int operator()(int a, int b) {
        cout << "functor" << endl;
        return a * b + x;
    }
private : 
    int x;
};

int main() {
    function<int(int, int)> func;
    func = add;
    cout << func(1, 3) << endl;
    Foo f1(3);
    func = f1;
    cout << func(2, 3) << endl;
    function<int(int, int)> func1;
    if (func1) {
        cout << "func1 Is Not Null" << endl;
    } else {
        cout << "func1 Is Null" << endl;
    }
    func1 = std::move(func);
    cout << func1(3, 7) << endl;
    func1 = nullptr;
    return 0;
}
