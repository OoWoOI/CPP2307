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

#define THREADHOLD 16

//无监督插入排序
void ungarded_insertion_sort(int *first, int *last, function<bool(int, int) > cmp = less<int>()) {
    int *ind = first;
    for (int *p = first + 1; p < last; p++) {
        if (cmp(*p, *ind)) ind = p; 
    }
    
    while (ind > first) {
        swap(*ind, *(ind - 1));
        ind -= 1;
    }

    for (int *i = (first + 2); i < last; i++) {
        ind = i;
        while (cmp(*(ind), *(ind - 1))) {
            swap(*(ind), *(ind - 1));
            ind -= 1;
        }
    }
    return ;
}

void quick_sort(int *first, int  *last, function<bool(int, int)> cmp = less<int>()) {
    while (last - first >= THREADHOLD) {
        int *x = first, *y = last - 1;
        int partion = *first;//三点取中法的优化思路
        do {
            while (cmp(*x, partion)) x++;
            while (cmp(partion, *y)) y--;
            if (x <= y) {
                swap(*x, *y);
                x++, --y;
            }
        } while (x <= y);
        quick_sort(x, last, cmp);
        last = x;
    }
    return ;
}

void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    quick_sort(first, last, cmp);
    ungarded_insertion_sort(first, last, cmp);
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

//实现sort函数带有迭代器
BEGIN(test3)


class RandomIt {
public :
    RandomIt(): ptr(nullptr) {};
    RandomIt(int *ptr) : ptr(ptr) {}; 
    
    int &operator*(){ return *(this->ptr);}
    RandomIt operator++(int) {return RandomIt(this->ptr++); }
    RandomIt &operator++() {this->ptr++;return *this;}
    RandomIt operator--(int) { return RandomIt(this->ptr--);}
    RandomIt operator--() { this->ptr++; return *this;}
    RandomIt operator=(const RandomIt &last) {this->ptr = last.ptr;return *this;}
    RandomIt operator+(int x) { return RandomIt(this->ptr + x);}
    int operator-(const RandomIt &last) { return last.ptr - this->ptr;}
    RandomIt operator-(int x) { return RandomIt(this->ptr - x);}

    bool operator<(const RandomIt &last) { return this->ptr < last.ptr; }
    bool operator>(const RandomIt &last) { return this->ptr > last.ptr; }
    bool operator<=(const RandomIt &last) { return this->ptr <= last.ptr;}
    bool operator!=(const RandomIt &last) { return this->ptr != last.ptr; }
    bool operator==(const RandomIt &last) { return this->ptr == last.ptr;}
    RandomIt &operator-=(int x) {this->ptr -= x; return *this;}
   


    ~RandomIt() {};   
private :
    int *ptr;
};


class CMP {
public :
    CMP() {}
    bool operator()(const int &a, const int &b) {
        return a < b;
    }
    ~CMP(){};
private :

};

void output(RandomIt first, RandomIt last, string str) {
    cout << str;
    for (RandomIt i = first; i != last; i++) {
        cout << *i <<  " ";
    }
    cout << endl;
    return ;
}

bool cmp1(const int &a, const int &b) {
    return a > b;
}

#define THREADHOLD 16

//无监督插入排序
void ungarded_insertion_sort(RandomIt first, RandomIt last, function<bool(int, int) > cmp = less<int>()) {
    RandomIt ind = first;
    for (RandomIt p = first + 1; p < last; p++) {
        if (cmp(*p, *ind)) ind = p; 
    }
    
    while (ind > first) {
        swap(*ind, *(ind - 1));
        ind -= 1;
    }

    for (RandomIt i = (first + 2); i < last; i++) {
        ind = i;
        while (cmp(*(ind), *(ind - 1))) {
            swap(*(ind), *(ind - 1));
            ind -= 1;
        }
    }
    return ;
}

void quick_sort(RandomIt first, RandomIt last, function<bool(int, int)> cmp = less<int>()) {
    while (last - first > THREADHOLD) {
        RandomIt x = first, y = last - 1;
        int partion = *first;//三点取中法的优化思路
        do {
            while (cmp(*x, partion)) x++;
            while (cmp(partion, *y)) y--;
            if (x <= y) {
                swap(x, y);
                x++, y--;
            }
        } while (x <= y);
        quick_sort(x, last, cmp);
        last = x;
    }
    return ;
}

void sort(RandomIt first, RandomIt last, function<bool(int, int)> cmp = less<int>()) {
    quick_sort(first, last, cmp);
    ungarded_insertion_sort(first, last, cmp);
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

END(test3)

int main() {
    //test1::main();
    //test2::main();
    test3::main();
    
    return 0;
}
