#include <cmath>
#include <iostream>
#include <stdexcept>
class Complex {
    double re,im;
public:
    Complex():re(0),im(0){}
    Complex(double r):re(r),im(0){}
    Complex(double r,double i):re(r),im(i){}
    Complex operator+(const Complex& z)const{return {re+z.re,im+z.im};}
    Complex operator-(const Complex& z)const{return {re-z.re,im-z.im};}
    Complex operator*(const Complex& z)const{return {re*z.re-im*z.im,re*z.im+im*z.re};}
    Complex operator/(const Complex& z)const{double d=z.re*z.re+z.im*z.im;if(d==0)throw std::domain_error("division by zero impedance");return {(re*z.re+im*z.im)/d,(im*z.re-re*z.im)/d};}
    bool operator==(const Complex& z)const{return std::abs(re-z.re)<1e-9&&std::abs(im-z.im)<1e-9;}
    double magnitude()const{return std::hypot(re,im);}
    friend std::ostream& operator<<(std::ostream& os,const Complex& z){return os<<z.re<<(z.im<0?" - ":" + ")<<std::abs(z.im)<<'j';}
};
int main(){Complex zR(10,0),zL(0,5),zC(0,-2);Complex series=zR+zL+zC;Complex parallel=(zR*zL)/(zR+zL);
    std::cout<<"Series impedance: "<<series<<", magnitude="<<series.magnitude()<<'\n';
    std::cout<<"Parallel impedance: "<<parallel<<", magnitude="<<parallel.magnitude()<<'\n';
    try{Complex invalid=zR/Complex();std::cout<<invalid<<'\n';}catch(const std::domain_error& e){std::cout<<"Safe error: "<<e.what()<<'\n';}}
