#include <iomanip>
#include <iostream>
#include <cstdlib>
class Money {
    long long paise;
public:
    Money(long long rupees=0,int p=0) : paise(rupees*100+p) {}
    Money operator+(const Money& rhs) const { Money result; result.paise=paise+rhs.paise; return result; }
    Money operator-(const Money& rhs) const { Money result; result.paise=paise-rhs.paise; return result; }
    Money& operator+=(const Money& rhs) { paise+=rhs.paise; return *this; }
    bool operator==(const Money& rhs) const { return paise==rhs.paise; }
    bool operator<(const Money& rhs) const { return paise<rhs.paise; }
    friend std::istream& operator>>(std::istream& in, Money& m) { long long rupees; int p; if (in >> rupees >> p) m.paise=rupees*100+p; return in; }
    friend std::ostream& operator<<(std::ostream& out,const Money& m) {
        long long a=std::llabs(m.paise); if(m.paise<0) out << '-';
        return out << "Rs " << a/100 << '.' << std::setw(2) << std::setfill('0') << a%100 << std::setfill(' ');
    }
};
int main(){ Money a(120,75),b(79,25); Money c=a+b; std::cout<<c<<'\n'<<std::boolalpha<<(c==Money(200))<<'\n';
    std::cout << Money(0,75)+Money(0,50) << '\n'; std::cout << Money(1)-Money(2) << '\n'; }
