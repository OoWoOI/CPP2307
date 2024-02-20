/*************************************************************************
	> File Name: 01.operator_concept.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 20 Feb 2024 08:57:11 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define __STL_REQUESTS(type, concept) do {\
    function<type, type> __test = type::concept(type, type);\
} while (0);


template <typename type>
class _LessThanComparable {
public :
    static type __operator_concept(type a, type a) {
        if (a < b) return a;
        return b;
    } 
};

class Base {
public :
    bool operator<(Base &obj) const {
        return true;
    }
};


int main() {
   __STL_REQUESTS(Base, _LessThanComparableable)); 
    
    return 0;
}
