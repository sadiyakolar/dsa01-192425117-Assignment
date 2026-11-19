#include <iostream>
#include <string>
class Person {
protected: std::string name,phone; int id;
public:
    Person(std::string n,int i,std::string p):name(n),phone(p),id(i){}
    virtual ~Person()=default;
};
class Student:virtual public Person {
protected: std::string programme; double cgpa;
public:
    Student(std::string n,int i,std::string p,std::string prog,double g)
      :Person(n,i,p),programme(prog),cgpa(g){}
};
class Staff:virtual public Person {
protected: std::string department; double salary;
public:
    Staff(std::string n,int i,std::string p,std::string d,double s)
      :Person(n,i,p),department(d),salary(s){}
};
class TeachingAssistant:public Student,public Staff {
public:
    TeachingAssistant(std::string n,int i,std::string p,std::string prog,double g,
                      std::string d,double s)
      :Person(n,i,p),Student(n,i,p,prog,g),Staff(n,i,p,d,s){}
    void display() const {
      std::cout<<"Teaching Assistant: "<<name<<" ID: "<<id
               <<" Programme: "<<programme<<" CGPA: "<<cgpa
               <<" Department: "<<department<<" Salary: "<<salary<<'\n';
    }
};
class Fellowship {
    double amount;
public: explicit Fellowship(double a):amount(a){}
    double getAmount() const{return amount;}
};
class ResearchScholar:public Student {
    Fellowship fellowship;
public:
    ResearchScholar(std::string n,int i,std::string p,std::string prog,double g,double f)
      :Person(n,i,p),Student(n,i,p,prog,g),fellowship(f){}
    void display() const {
      std::cout<<"Research Scholar: "<<name<<" Fellowship: "<<fellowship.getAmount()<<'\n';
    }
};
int main() {
    TeachingAssistant ta("Kavya",201,"9876543210","MCA",8.7,"Computer Science",25000);
    ResearchScholar rs("Arun",202,"9876501234","PhD",9.1,18000);
    ta.display(); rs.display();
}
