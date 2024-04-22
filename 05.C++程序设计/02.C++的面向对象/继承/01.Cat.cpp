/*************************************************************************
	> File Name: 01.Cat.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Apr 2024 06:05:50 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

class Base {
public :
    int x;
protected :
    int y;
private :
    int z;
};

class public_base : public Base {
public :
    void main() {
        this->x;
        this->y;
        //this->z;
    }
};

class protected_base : protected Base {
public :
    void main() {
        this->x;
        this->y;
        //this->z;
    }
};

class private_base : private Base {
public :
    void main() {
        this->x;
        this->y;
        //this->z;
    }
};

int main() {
    public_base a;

    a.x;   //YES, public + public   = public;
    //a.y; //NO, public + protected = protected;
    //a.z; //NO, public + private   = private;
    
    protected_base b;

    //b.x; //NO, protected + public   = protected;
    //b.y; //NO, protected + protected = protected;
    //b.z; //NO, protected + private   = private;
    
    private_base c;

    //c.x; //NO, private + public   = private;
    //c.y; //NO,   private + protected = private;
    //c.z; //NO,   private + private   = private;
  
    
    return 0;
}
