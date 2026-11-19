#include <iomanip>
#include <iostream>
#include <string>
class Cart {
    std::string items[10]; double prices[10]; int n=0; double discount=0;
public:
    Cart& add(const std::string& item,double price) {
        if(n<10 && price>=0){items[n]=item;prices[n]=price;++n;}
        return *this;
    }
    Cart& setDiscount(double discount) {
        if(discount>=0 && discount<=100) this->discount=discount;
        return *this;
    }
    double total() const {
        double sum=0;for(int i=0;i<n;++i)sum+=prices[i];
        return sum*(100-discount)/100;
    }
};
int main() {
    Cart c;c.add("Rice",60).add("Dal",120).setDiscount(10);
    Cart* p=&c;p->add("Oil",180);
    Cart& ref=c;ref.add("Soap",40);
    Cart* dynamicCart=new Cart;dynamicCart->add("Milk",50);
    std::cout<<"Dynamic cart: "<<dynamicCart->total()<<'\n';delete dynamicCart;
    std::cout<<std::fixed<<std::setprecision(2)<<"Customer cart: "<<c.total()<<'\n';
    Cart a,b,d;a.add("Book",100);b.add("Bag",500);d.add("Shoes",1200);
    Cart* carts[3]={&a,&b,&d};int best=0;
    for(int i=1;i<3;++i)if(carts[i]->total()>carts[best]->total())best=i;
    std::cout<<"Highest cart: "<<carts[best]->total()<<'\n';
}
