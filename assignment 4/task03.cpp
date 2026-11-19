#include <iostream>
#include <string>
class Address {
    std::string city; int pin;
public:
    Address(std::string c,int p):city(c),pin(p){std::cout<<"Address constructed\n";}
    ~Address(){std::cout<<"Address destroyed\n";}
    std::string str() const{return city+"-"+std::to_string(pin);}
};
class Course {
    std::string title;
public:
    explicit Course(std::string t):title(t){std::cout<<"Course constructed\n";}
    ~Course(){std::cout<<"Course destroyed\n";}
};
class Person {
protected: std::string name; int age;
public:
    Person(std::string n,int a):name(n),age(a){std::cout<<"Person constructed\n";}
    virtual ~Person(){std::cout<<"Person destroyed\n";}
};
class Student:public Person {
    long long regNo; Address home; Course course;
public:
    Student(std::string n,int a,long long r,std::string city,int pin,std::string c)
      :Person(n,a),regNo(r),home(city,pin),course(c){std::cout<<"Student constructed\n";}
    ~Student() override {std::cout<<"Student destroyed\n";}
    void print() const {
      std::cout<<regNo<<' '<<name<<" ("<<age<<") "<<home.str()<<'\n';
    }
};
struct Engine {Engine(){std::cout<<"Engine ";} ~Engine(){std::cout<<"~Engine ";}};
struct Vehicle {Vehicle(){std::cout<<"Vehicle ";} virtual ~Vehicle(){std::cout<<"~Vehicle ";}};
struct Car:Vehicle {Engine e; Car(){std::cout<<"Car ";} ~Car() override {std::cout<<"~Car ";}};
int main() {
    {Student s("Kavya",19,192311001,"Salem",636001,"C++");s.print();}
    std::cout<<"Order: ";
    {Car c; std::cout<<"| ";}
    std::cout<<'\n';
}
