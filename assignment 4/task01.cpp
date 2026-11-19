#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <iomanip>
class Staff {
    std::string name; int id; double basic;
protected:
    double basicPay() const { return basic * 1.42; }
public:
    Staff(std::string n,int i,double b):name(n),id(i),basic(b){}
    virtual double pay() const=0;
    virtual void display() const {
        std::cout<<name<<" ("<<id<<") : Rs "<<std::fixed<<std::setprecision(2)<<pay()<<'\n';
    }
    virtual ~Staff()=default;
};
class Professor:public Staff {
    double research;
public:
    Professor(std::string n,int i,double b,double r):Staff(n,i,b),research(r){}
    double pay() const override { return basicPay()+research; }
};
class LabAssistant:public Staff {
public:
    LabAssistant(std::string n,int i,double b):Staff(n,i,b){}
    double pay() const override { return basicPay(); }
};
class GuestFaculty:public Staff {
    double hours,rate;
public:
    GuestFaculty(std::string n,int i,double h,double r):Staff(n,i,0),hours(h),rate(r){}
    double pay() const override { return hours*rate; }
};
int main() {
    std::vector<std::unique_ptr<Staff>> staff;
    staff.push_back(std::make_unique<Professor>("Asha",101,50000,8000));
    staff.push_back(std::make_unique<LabAssistant>("Bala",102,30000));
    staff.push_back(std::make_unique<GuestFaculty>("Chitra",103,40,1000));
    for(const auto& s:staff) s->display();
}
