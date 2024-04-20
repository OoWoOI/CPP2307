/*************************************************************************
	> File Name: 02.sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 20 Apr 2024 11:06:46 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;

#define BEGIN(x) namespace x {
#define END(x) }


//sort基本使用
BEGIN(test1)

class CMP {
public :
    CMP() {}
    bool operator()(const int &a, const int &b) {
        return a < b;
    }
    ~CMP(){};
private :

};

void output(int *first, int *last, string str) {
    cout << str;
    for (int *i = first; i != last; i++) {
        cout << *i <<  " ";
    }
    cout << endl;
    return ;
}

bool cmp1(const int &a, const int &b) {
    return a < b;
}

int main() {
    int arr[100], n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");
    sort(arr, arr + n, cmp1);
    output(arr, arr + n, "cmp1 : ");
    CMP cmp2;
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "cmp2 : ");

    return 0;
}

END(test1)

//实现sort函数
BEGIN(test2)

class CMP {
public :
    CMP() {}
    bool operator()(const int &a, const int &b) {
        return a < b;
    }
    ~CMP(){};
private :

};

void output(int *first, int *last, string str) {
    cout << str;
    for (int *i = first; i != last; i++) {
        cout << *i <<  " ";
    }
    cout << endl;
    return ;
}

bool cmp1(const int &a, const int &b) {
    return a < b;
}


void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    //TODO
    return ;
}

int main() {
    int arr[100], n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");
    sort(arr, arr + n, cmp1);
    output(arr, arr + n, "cmp1 : ");
    CMP cmp2;
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "cmp2 : ");

    return 0;
}

END(test2)

int main() {
    test1::main();
    
    return 0;
}
