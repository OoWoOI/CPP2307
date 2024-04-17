/*************************************************************************
	> File Name: constrcutor.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 17 Apr 2024 02:33:25 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Data {
public :
    Data() :_x(100), _y(100) {
        cout << "default constrcutor" << endl;
    } 
    int x() {return _x; };
    int y() {return _y; };
    ~Data() {
        cout << "destrcutor" << endl;
    }
private :
    int _x, _y;
};

int main() {
    Data d; 
    cout << d.x() << endl;
    cout << d.y() << endl;
    return 0;
}
