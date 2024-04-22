/*************************************************************************
	> File Name: HZOJ-256.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Apr 2024 03:24:55 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class BigInt : public vector<int> {
public :
    
    BigInt(int x) {
        push_back(x);
        proccess_digit();
    }

    bool operator<(const BigInt &a) {
        if (size() - a.size()) return size() < a.size();
        for (int i = size() - 1; i >= 0; i--) {
            if (at(i) - a[i]) return at(i) < a[i];
        }
        return false;
    }

    void operator*=(int x) {
        for (int i = 0; i < size(); i++) at(i) *= x;
        proccess_digit();
        return ;
    }
     void operator/=(int x) {
        int y = 0;
        for (int i = size() - 1; i >= 0; i--) {
            y = y * 10 + at(i);
            at(i) = y / x;
            y %= x;
        }
        proccess_digit();
        return ;
    }

    BigInt operator/(int x) {
        BigInt ret(*this);
        int y = 0;
        ret /= x;
        return ret;
    }

   
private :
    void proccess_digit() {
        for (int i = 0; i < size(); i++) {
            if (at(i) < 10) continue;
            if (i + 1 == size()) push_back(0);
            at(i + 1) += at(i) / 10;
            at(i) %= 10;
        }
        while (size() > 1 && at(size() - 1) == 0) pop_back();
        return ;
    }

};


struct  Data {
    int a, b;
};


ostream &operator<<(ostream &out, const BigInt &a) {
    for (int i = a.size() - 1; i >= 0; --i) {
        out << a[i];
    }
    return out;
}

int main() {
    int n;
    vector<Data> arr;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        Data temp;
        cin >> temp.a >> temp.b;
        arr.push_back(temp);
    }
    sort(arr.begin() + 1, arr.end(), [](const Data &x, const Data &y){
        return x.a * x.b < y.a * y.b;
    });
    BigInt ans = 0, p = arr[0].a;
    for (int i = 1; i <= n; i++) {
        BigInt temp = p / arr[i].b;
        if (ans < temp) ans = temp;
        p *= arr[i].a;
    }
    cout << ans << endl;
    return 0;
}
