/*************************************************************************
	> File Name: 03.rvalue_move.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 30 Apr 2024 08:00:50 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)

template<class T>
class Arrary {
public :
    Arrary() : __size(5), data(new T[__size]) {
        cout << "default constructor" << endl;
    }
    Arrary(int x) : __size(x), data(new T[__size]) {
        cout << "Arrary size constructor" << endl;
    }
    Arrary(Arrary<T> &&a) : __size(a.__size), data(a.data) {
        cout << "move constructor" << endl;
        a.data = nullptr;
        a.__size = 0;
    }
    
    T &operator[](int ind) {
        return data[ind];
    }

    Arrary operator+(Arrary<T> &a) {
        Arrary<T> ret(__size + a.__size);
        for (int i = 0; i < __size; i++) {
            ret[i] = data[i];
        }
        for (int i = __size; i < ret.__size; i++) {
            ret[i] = a[i - __size];
        }
        return ret; 
    }
    
    int size() {return __size;};
    
    ~Arrary() {
        cout << "destructor" << endl;
    }

private :
    int __size;
    T *data;
};

int main() {
    Arrary<int> a, b;
    Arrary<int> c = a + b;
    return 0;
}

ENDS(test1)


int main() {
    test1::main();
    return 0;
}
