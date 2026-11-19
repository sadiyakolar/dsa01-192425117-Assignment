#include <iostream>
#include <string>
using namespace std;

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

// int means grams; double means kilograms. Defaults are trailing optional arguments.
void charge(int grams) {
    cout << "Grams overload: " << grams << " g, charge Rs " << 20 + grams / 100 << '\n';
}

void charge(double kilograms, bool express = false, bool insured = false) {
    double amount = 30.0 + kilograms * 12.0;
    if (express) amount += 25.0;
    if (insured) amount += 10.0;
    cout << "Kilograms overload: " << kilograms << " kg, express=" << boolalpha
         << express << ", insured=" << insured << ", charge Rs " << amount << '\n';
}

void charge(const Parcel& parcel) {
    cout << "Parcel overload selected: ";
    charge(parcel.weightKg, parcel.express, parcel.insured);
}

int main() {
    Parcel p{2.5, true, false};
    cout << "Call 1: charge(2)\n";
    charge(2);             // exact match: int grams
    cout << "Call 2: charge(2.0)\n";
    charge(2.0);           // exact match: double kilograms
    cout << "Call 3: charge(2.0f)\n";
    charge(2.0f);          // float promotes to double
    cout << "Call 4: charge(500)\n";
    charge(500);           // exact match: int grams
    cout << "Call 5: charge(1.5, true)\n";
    charge(1.5, true);     // double overload; insured uses default false
    cout << "Call 6: charge(parcel)\n";
    charge(p);             // Parcel overload
}
