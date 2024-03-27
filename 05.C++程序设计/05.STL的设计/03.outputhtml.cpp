/*************************************************************************
	> File Name: 03.outputhtml.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 17 Mar 2024 10:36:05 AM CST
 ************************************************************************/

#include <iostream>
#include <sstream>
using namespace std;

class PersonElement;
class PersonBuilder;
class PersonBaseInfoBuilder;

class PersonElement {
public :
    static PersonBuilder *build();
    // base info
    string name;
    int age;
    double height;
    // work info
    string company;
    int level;
};

class PersonBuilder {
public :
    PersonElement person;
    operator PersonElement() const { return person; }
    PersonBaseInfoBuilder BaseInfo();
};

class PersonBaseInfoBuilder : public PersonBuilder {
public :
    typedef PersonBaseInfoBuilder &Self;
    PersonElement person;
    PersonBaseInfoBuilder(PersonElement &&person) : person(std::move(person)) {}
    Self name(string n) { person.name = n; return *this;}
    Self age(int a) { person.age = a; return *this;}
    Self height(double h) { person.height = h; return *this;}
};

PersonBuilder *PersonElement::build() { 
    return new PersonBuilder();
}

PersonBaseInfoBuilder PersonBuilder::BaseInfo() {
    return PersonBaseInfoBuilder(std::move(person));
}

int main() {
    PersonElement person = PersonElement::build()
    ->BaseInfo().name("hug").age(56).height(2.92);
    return 0;
}
