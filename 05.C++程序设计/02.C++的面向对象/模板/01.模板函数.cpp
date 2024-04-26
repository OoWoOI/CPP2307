/*************************************************************************
	> File Name: 01.模板函数.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Apr 2024 03:43:53 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;


#define BEGINGS(x) namespace x {
#define ENDS(x) }

BEGINGS(test1) 

template<typename T>
T add(T a, T b) {
    return a + b;
}


int main() {
    cout << "add(3, 4) = " << add(3, 4) << endl;;
    cout << "add(3.2, 4.4) = " << add(3.2, 4.4) << endl;
    return 0;
}

ENDS((test1))

BEGINGS(test2) 

template<typename T, typename U>
decltype(T() + U()) add(T a, U b) {//动态类型计算：decltype, 但是对于删除默认构造类型不友好
    return a + b;
}


int main() {
    cout << "add(3, 4.2) = " << add(3, 4.2) << endl;;
    cout << "add(3.2, 4) = " << add(3.2, 4) << endl;
    return 0;
}

ENDS((test2))

BEGINGS(test3) 

template<typename T, typename U>
auto  add(T a, U b)->decltype(T() + U()) {//返回值后置，解决默认构造函数删除的隐患
    return a + b;
}


int main() {
    cout << "add(3, 4.2) = " << add(3, 4.2) << endl;;
    cout << "add(3.2, 4) = " << add(3.2, 4) << endl;
    return 0;
}

ENDS((test3))

int main() {
    
    test3::main(); 
    
    return 0;
}
