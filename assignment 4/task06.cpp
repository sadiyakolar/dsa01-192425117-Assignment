#include <iostream>
#include <string>
class Vehicle {
protected: std::string reg; double dailyRate; bool rented=false;
public:
    Vehicle(std::string r,double rate):reg(r),dailyRate(rate){}
    virtual double rentalCharge(int days) const=0;
    bool rent(){if(rented)return false;rented=true;return true;}
    double returnVehicle(int used,int allowed) {
        if(!rented)return 0;
        rented=false;int late=used>allowed?used-allowed:0;
        return rentalCharge(used)+late*200.0;
    }
    virtual void display() const=0;
    virtual ~Vehicle()=default;
};
class Bicycle:public Vehicle {
public:
    Bicycle(std::string r,double rate):Vehicle(r,rate){}
    double rentalCharge(int days) const override{return dailyRate*days;}
    void display() const override{std::cout<<"Bicycle "<<reg<<'\n';}
};
class MotorVehicle:public Vehicle {
protected: double fuelLevel; std::string serviceDue;
public:
    MotorVehicle(std::string r,double rate,double fuel,std::string date)
      :Vehicle(r,rate),fuelLevel(fuel),serviceDue(date){}
};
class TwoWheeler:public MotorVehicle {
public:
    TwoWheeler(std::string r,double rate,double fuel,std::string date)
      :MotorVehicle(r,rate,fuel,date){}
    double rentalCharge(int days) const override{return dailyRate*days+50;}
    void display() const override{std::cout<<"Two-wheeler "<<reg<<" fuel "<<fuelLevel<<" service "<<serviceDue<<'\n';}
};
class Car:public MotorVehicle {
    int seats;
public:
    Car(std::string r,double rate,double fuel,std::string date,int s)
      :MotorVehicle(r,rate,fuel,date),seats(s){}
    double rentalCharge(int days) const override{return dailyRate*days+seats*25;}
    void display() const override{std::cout<<"Car "<<reg<<" seats "<<seats<<'\n';}
};
class ElectricCar:public Vehicle {
protected: double batteryKwh,ratePerKwh;
public:
    ElectricCar(std::string r,double rate,double battery,double kwhRate)
      :Vehicle(r,rate),batteryKwh(battery),ratePerKwh(kwhRate){}
    double rentalCharge(int days) const override{return dailyRate*days+batteryKwh*ratePerKwh;}
    void display() const override{std::cout<<"Electric car "<<reg<<" battery "<<batteryKwh<<" kWh\n";}
};
class ElectricBus:public ElectricCar {
    int seats;
public:
    ElectricBus(std::string r,double rate,double battery,double kwhRate,int s)
      :ElectricCar(r,rate,battery,kwhRate),seats(s){}
    double rentalCharge(int days) const override{return dailyRate*days+batteryKwh*ratePerKwh+seats*10;}
    void display() const override{std::cout<<"Electric bus "<<reg<<" seats "<<seats<<'\n';}
};
int main() {
    Bicycle bike("CYC101",100);
    TwoWheeler two("TN01AB1234",250,5,"2027-01-10");
    Car car("TN01CD5678",1200,35,"2027-02-15",5);
    ElectricCar ev("TN01EV1111",1500,60,8);
    ElectricBus bus("TN01EB2222",3000,180,8,30);
    Vehicle* fleet[5]={&bike,&two,&car,&ev,&bus};
    for(Vehicle* v:fleet){v->display();std::cout<<(v->rent()?"Rented":"Unavailable")<<'\n';}
    std::cout<<"Late car return charge: Rs "<<car.returnVehicle(4,2)<<'\n';
    std::cout<<"Bicycle return charge: Rs "<<bike.returnVehicle(2,2)<<'\n';
}
