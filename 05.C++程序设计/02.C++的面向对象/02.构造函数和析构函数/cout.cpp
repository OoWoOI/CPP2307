/*************************************************************************
	> File Name: cout.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Apr 2024 06:51:06 PM CST
 ************************************************************************/

#include<iostream>
#include<cstdio>
using namespace std;

#define BEGIN(x) namespace x {
#define END(x) }


BEGIN(haizei)
class ostream {
public :
    ostream &operator<<(int x);
    ostream &operator<<(char y);
};
ostream &ostream::operator << (int x) {
        printf("%d", x);
        return *this;
    }
    
ostream &ostream::operator << (char x) {
        printf("%c", x);
        return *this;
    }
const char endl = '\n';

ostream cout;

END(haizei)

int main() {
    haizei::cout << 123 << haizei::endl;
    std::cout << 123 << std::endl;
    return 0;
}
