/*************************************************************************
	> File Name: class.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Apr 2024 05:10:45 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGIN(x) namespace x{
#define END(x) }

BEGIN(haizei)

class People {
public :
    People() {}
    string name;
    void say(string name) {
        cout << name << endl;
        cout << this->name << endl;
    }
};
    
END(haizei)


int main() {
    haizei::People hug;
    
    hug.name = "hug";
    hug.say("xiao hu");
    
    return 0;
}
