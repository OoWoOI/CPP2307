/*************************************************************************
	> File Name: 01.shared_ptr.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 20 Apr 2024 09:14:31 PM CST
 ************************************************************************/

#include<iostream>
#include<memory>
#define BEGIN(x) namespace x { 
#define END(x) }




BEGIN(test1)

class A {
public :
    A() {
        std::cout << "default constructor" << std::endl;
    }
    ~A() {
        std::cout << "destructor" << std::endl;
    }
private :

};

//智能指针简单测试
int main() {
    std::shared_ptr<A> p = std::make_shared<A>();
    std::cout << "p->use_count = " <<  p.use_count() << std::endl;
    std::shared_ptr<A> q = p;
    std::cout << "p->use_count = " <<  p.use_count() << std::endl;
    std::cout << "q->use_count = " << q.use_count() << std::endl;
    p = nullptr;
    std::cout << "q->use_count = " <<  q.use_count() << std::endl;
    q = nullptr;
    std::cout << "end main"<< std::endl;
    //环形引用问题
    return 0;
}

END(test1)

BEGIN(test2)

class A {
public :
    A() {
        std::cout << "default constructor" << std::endl;
    }
    ~A() {
        std::cout << "destructor" << std::endl;
    }
    std::shared_ptr<A> p;
};

//智能指针简单测试
int main() {
    std::shared_ptr<A> p = std::make_shared<A>();
    std::shared_ptr<A> q = std::make_shared<A>();
    p->p = q;
    q->p = p;
    //环形引用问题
    p = nullptr;
    q = nullptr;
    std::cout << "end main" << std::endl;
    return 0;
}
END(test2)

BEGIN(test3)
class A {
public :
    A() {
        std::cout << "default constructor" << std::endl;
    }
    int x, y;
    ~A() {
        std::cout << "destructor" << std::endl;
    }
private :

};

class ptr_data {
public :
    ptr_data(A *ptr, int *cnt = nullptr) : ptr(ptr), cnt(cnt) {
        if (this->cnt == nullptr) this->cnt = new int(1);
    }
    void increase_one() const {
        *cnt += 1;
        return ;
    }
    void decrease_one()const {
        *cnt -= 1;
        if (*cnt == 0) delete ptr;
        return ;
    }

    bool operator==(const ptr_data &p) const {
        return p.ptr == ptr && p.cnt == cnt;
    }
    
    ~ptr_data(){
        decrease_one();
        if (*cnt == 0) delete cnt;

    }


    A *ptr;
    int *cnt;
};


class shared_ptr {

public :
    shared_ptr(A *ptr) : p(ptr) {}
    shared_ptr(const shared_ptr &p) : p(p.p) {
        this->p.increase_one();
    }//拷贝构造
    shared_ptr &operator=(const shared_ptr &obj) {
        if (obj.p == this->p) return *this;
        p.decrease_one();
        p = obj.p;
        p.increase_one();
        return *this;
    }
    A *operator->() {return p.ptr;}
    A &operator*() {return *p.ptr;}
    int use_count() {return *p.cnt;}
    
    ~shared_ptr() {
        
    }

private :
    ptr_data p;
};


shared_ptr make_shared() {
    return shared_ptr(new A()); 
}

std::ostream &operator<<(std::ostream &out, A &a) {
    out << a.x << " " << a.y; 
    return out;
}

//智能指针简单测试
int main() {
    shared_ptr p = make_shared();
    p->x = 3, p->y = 4;
    std::cout << *p << std::endl;
    std::cout << "p->use_count = " <<  p.use_count() << std::endl;
    shared_ptr q = p;
    std::cout << "p->use_count = " <<  p.use_count() << std::endl;
    std::cout << "q->use_count = " << q.use_count() << std::endl;
    p = nullptr;
    std::cout << "q->use_count = " <<  q.use_count() << std::endl;
    q = nullptr;
    std::cout << "end main"<< std::endl;
    //环形引用问题
    return 0;
}


END(test3)


int main() {
    test1::main();  
    //test2::main();
    test3::main();
    return 0;
}
