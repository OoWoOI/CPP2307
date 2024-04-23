/*************************************************************************
	> File Name: execpt.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 23 Apr 2024 06:58:06 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class MyException : public runtime_error {
public : 
    MyException(string msg) : runtime_error(msg) {
        cout << "MyException ctor" << endl;
    }
    const char *what() const noexcept override {
        return "123";
    }
};


int main() {
    try {
        throw (MyException("hello world!"));
    } catch (runtime_error &re) {
        cout << re.what() << endl;
    }
     
    return 0;
}
