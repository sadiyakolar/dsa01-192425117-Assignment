#include <iostream>
#include <memory>
#include <vector>
class Account {
public:
    double rate() const{return 3.5;}
    virtual double virtualRate() const{return 3.5;}
    virtual ~Account(){std::cout<<"Account destroyed\n";}
};
class SeniorAccount:public Account {
    double* history;
public:
    SeniorAccount():history(new double[100]{}){}
    double rate() const{return 4.0;}
    double virtualRate() const override{return 4.0;}
    ~SeniorAccount() override {delete[] history;std::cout<<"SeniorAccount destroyed\n";}
};
int main() {
    SeniorAccount senior;
    Account* p=&senior;
    Account sliced=senior;
    std::cout<<p->rate()<<' '<<p->virtualRate()<<' '<<sliced.virtualRate()<<'\n';
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for(const auto& a:accounts) std::cout<<a->virtualRate()<<'\n';
}
