/*************************************************************************
	> File Name: 05.HashTable.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Apr 2024 04:24:33 PM CST
 ************************************************************************/

#include<iostream>
#include<functional>
#include<vector>
#include<string>
using namespace std;


/**
 *
 * 实现自定义哈希函数的哈希表
 * (1) 实现哈希表功能
 * (2) 根据哈希表功能抽象出来一个接口类
 */

class HASH {
public : 
    virtual bool insert(string, int) = 0;
    virtual bool erase(string) = 0;
    virtual bool find(string) = 0;
    virtual int capacity() const = 0;
    virtual int &operator[](string) = 0;
    virtual~HASH(){};
};

class APHash_Class {
public : 
    int operator()(string s) {
        int h = 0;
        for (int i = 0; s[i]; i++) {
            if (i % 2) {
                h = (h << 3) ^ s[i] ^ (h >> 5);
            } else {
                h = ~((h << 7) ^ s[i] ^ (h >> 11));
            }
        }
        return h & 0x7fffffff;
    }
};

int BKDRHash(string s) {
    int seed = 31;
    int h = 0;
    for (int i = 0; s[i]; i++) h = h * seed + s[i];
    return h & 0x7fffffff;
}



class Node {
public :
    Node() = default;
    Node(string, int);
    string key() const;
    int value() const;
    Node *next() const;
    void set_next(Node *);
    void insert(Node *);
    void erase_next();
    friend class HashTable;
private :
    string __key;
    int __value;
    Node *__next;
};

Node::Node(string s, int val = -1) :
    __key(s),
    __value(val),
    __next(nullptr)
{
    //转换构造
}


string Node::key() const {
    return this->__key;
}

int Node::value() const {
    return this->__value;
}

Node *Node::next() const {
    return this->__next;
}

void Node::set_next(Node *p) {
    this->__next = p;
    return ;
}

void Node::insert(Node *p) {
    p->set_next(this->__next);
    this->set_next(p);
    return ;
}


void Node::erase_next() {
    Node *p = this->__next;
    if (p) {
        this->__next = p->__next;
    } else {
        this->__next = nullptr;
    }
    delete p;
    return ;
}



class HashTable : public HASH {
public :    
    typedef function<int(string)> HASH_FUNC_T;
    HashTable();
    HashTable(HASH_FUNC_T = BKDRHash, int = 10);
    bool insert(string, int = -1) override;
    bool erase(string) override;
    bool find(string) override;
    int capacity() const override;
    int &operator[](string) override;
    void show();
    ~HashTable();
private :
    Node *__insert(string, int = -1);
    Node *__find(string);
    void __expand();
    int __size, data_cnt;
    vector<Node> data;
    HASH_FUNC_T hash_func;
};

//实现哈希表功能

HashTable::HashTable() : 
    __size(10), 
    data_cnt(0), 
    data(vector<Node>(__size)),
    hash_func(BKDRHash) 
{
    //默认构造函数-哈希表    
}

HashTable::HashTable(HASH_FUNC_T hash_func, int size) :
    __size(size), 
    data_cnt(0),
    data(vector<Node>(__size)),
    hash_func(hash_func) 
{
    //有参构造函数-哈希表
}


HashTable::~HashTable() {
    for (int i = 0; i < capacity(); i++) {
        if (data[i].next() == nullptr) continue;
        Node *p = data[i].next();
        while (p) {
            Node *q = p;
            delete q;
            p = p->next();
        }
    }
    delete[] &data;
}


int HashTable::capacity() const {
    return this->__size;
}


void HashTable::__expand() {
    return ;
}

Node *HashTable::__insert(string s, int val) {
    if (data_cnt >= 2 * capacity()) __expand();
    int ind = hash_func(s) % __size;
    Node *p = new Node(s, val);
    data[ind].insert(p);
    data_cnt += 1;
    return p; 
}

bool HashTable::insert(string s, int val) {
    Node *p = __insert(s, val);
    return p != nullptr;
}

Node* HashTable::__find(string s){
    Node *p = nullptr;
    int ind = hash_func(s) % capacity();
    p = &data[ind];
    while (p->next() != nullptr && p->next()->key() != s) {
        p = p->next();
    } 
    return p->next() != nullptr ? p : nullptr;
}

bool HashTable::find(string s) {
    Node *p = __find(s);
    return p != nullptr;
} 

bool HashTable::erase(string s) {
    if (!find(s) || data_cnt == 0) return false;
    Node *p = __find(s);
    if (p == nullptr) return false;
    p->erase_next();
    data_cnt -= 1;
    return true;
}

int& HashTable::operator[](string s) {
    Node *p = __find(s);
    p = (p ? p->next() : __insert(s));
    return p->__value;
}

void HashTable::show() {
    cout << "hash table : [" << capacity() << "]" << endl;

    for (int i = 0; i < capacity(); i++) {
        if (data[i].next() == nullptr) continue;
        Node *p = data[i].next();
        while (p) {
            cout << p->key() << " : " << p->value() << " -> ";
            p = p->next();
        }
        cout << endl;
    }

    return ;
}

int main() {
    APHash_Class APHash;
    HashTable h1(BKDRHash);
    HashTable h2(APHash);
    int op;
    string s;
    cout << h1.capacity() << endl;
    cout << h2.capacity() << endl;
    h1["hello"] = 123;
    h1["world"] = 456;
    h1["haizei"] = 789;
    cout << h1.capacity() << endl;
    cout << h2.capacity() << endl;
    cout << h1["hello"] << " " << h1["world"] << " " << h1["haizei"] << endl;
    while (cin >> op >> s) {
        switch (op) {
            case 0: {
                cout << "insert " << s << " to hash table 1 =  ";
                cout << h1.insert(s) << endl;
                cout << "insert " << s << " to hash table 2 =  ";
                cout << h2.insert(s) << endl;
            } break;
            case 1 : {
                //删除
                cout << "erase " << s << " from hash table 1 =  ";
                cout << h1.erase(s) << endl;
                cout << "erase " << s << " from hash table 2 =  ";
                cout << h2.erase(s) << endl;
            } break;//erase
            case 2: {
                //查找
                cout << "find " << s << " at hash table 1 = ";
                cout << h1.find(s) << endl;
                cout << "find " << s << " at hash table 2 = ";
                cout << h2.find(s) << endl;
            } break;//find
        }
        h1.show();
        h2.show();
    }
    return 0;
}
