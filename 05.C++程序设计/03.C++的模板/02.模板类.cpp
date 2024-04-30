/*************************************************************************
	> File Name: 02.模板类.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Apr 2024 03:55:02 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;


#define BEGINS(x) namespace x {
#define ENDS(x) }


BEGINS(test1)

template<typename T>
class printAny {
public :
    printAny(ostream &out) : out(cout) {}
    
    printAny &print(T a) {
        out << a;
        return *this;
    }
    printAny &endl() {
        out << std::endl;
        return *this;
    }
private :
    ostream &out;
};

int main() {
    printAny<int> pint(std::cout);
    printAny<string> pstr(std::cout);
    printAny<float> pfloat(std::cout);
    pint.print(3).endl();
    pstr.print("123").endl();
    pfloat.print(1.23).endl();
    return 0;
}

ENDS(test1)

BEGINS(test2)

class printAny {
public :
    printAny(ostream &out) : out(cout) {}
    
    template<typename T>
    printAny &print(T a) {
        out << a;
        return *this;
    }
    printAny &endl() {
        out << std::endl;
        return *this;
    }
private :
    ostream &out;
};

int main() {
    printAny p(std::cout);
    p.print(3).endl().print("123").endl().print(1.23).endl();
    return 0;
}

ENDS(test2)


int main() {
    test2::main();
    return 0;
}
