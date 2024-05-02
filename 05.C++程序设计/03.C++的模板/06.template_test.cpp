/*************************************************************************
	> File Name: 06.template_test.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 02 May 2024 11:04:45 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }


BEGINS(sum_test)

template<int N>
class NUM {
public : 
    static constexpr int r = (N + 1) * N / 2;
};

template<>
class NUM<1> {
    public :
    static constexpr int r = 1;
};



int main() {
    cout << "NUM(100) SUM : " << NUM<101>::r << endl;
    return 0;
}

ENDS(sum_test)

BEGINS(is_even)


template<int N> class IS_EVEN;
template<>
class IS_EVEN<0> {
public :
    static constexpr const char *str = "YES";
};

template<>
class IS_EVEN<1> {
public :
    static constexpr const char* str = "NO";
};

template<int N>
class NUM {
public :
    static constexpr const char *is_even = IS_EVEN<N % 2>::str;
};

int main() {
    cout << "NUM(10) is EVEN : " << NUM<10>::is_even << endl;
    return 0;
}

ENDS(is_even)


BEGINS(score_level)


template<int N> class CALC;
template<> 
class CALC<0> {
public :
    static constexpr const char * str = "bad";
};
template<> 
class CALC<1> {
public :
    static constexpr const char * str = "good";
};

template<int N>
class SCORE {
public :
    static constexpr const char* level = CALC<(N >= 60)>::str;
};

int main() {
    cout << "score : 80 = " << SCORE<80>::level << endl;
    cout << "score : 54 = " << SCORE<54>::level << endl;
    return 0;
}

ENDS(score_level)

BEGINS(is_prime)
/**
template<int N, int M>
class IS_PRIME {
public :
    static constexpr const char *is = ((M > 1) && (N % M) == 0) ? "NO" : IS_PRIME<N, M - 1>::is;
};

template<int N>
class IS_PRIME<N, 1> {
public :
    static constexpr const char *is = "YES";
};

template<int N>
class NUM {
public:
    static constexpr const char *str = IS_PRIME<N, N / 2>::is;
};
**/

template<int N>
class NUM {
private :
    static constexpr bool is_prime(int num) {
        if (num > 1 && num <= 3) return true;
        for (int i = num / 2; i > 1; i--) {
            if (num % i == 0) return false;
        }
        return true;
    }
public :
    static constexpr const char *str = is_prime(N) ? "yes" : "no";

};


int main() {
    cout << "is_prime<2>::r " << NUM<2>::str <<endl;//yes
    cout << "is_prime<3>::r " << NUM<3>::str <<endl;//yes
    cout << "is_prime<5>::r " << NUM<5>::str << endl;//yes
    cout << "is_prime<8>::r " << NUM<8>::str << endl;//no
    cout << "is_prime<9973>::r " << NUM<9973>::str << endl;//no
    return 0;
}

ENDS(is_prime)

int main() {
    sum_test::main();
    is_even::main();
    score_level::main();
    is_prime::main();
    return 0;
}
