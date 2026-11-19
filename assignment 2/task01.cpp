#include <iostream>
using namespace std;

// Call by value: only the local copy changes.
void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
    cout << "Inside call by value: " << fee << '\n';
}

// Call by reference: the caller's fee changes.
void applyByReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}

// Call by pointer: the pointed-to caller's fee changes.
void applyByPointer(long long* fee, int percent) {
    if (fee != nullptr) *fee -= *fee * percent / 100;
}

// Alternative: return the updated fee instead of modifying it.
long long applyAndReturn(long long fee, int percent) {
    return fee - fee * percent / 100;
}

void change(int a, int& b, int* c) {
    a += 10;
    b += 10;
    *c += 10;
}
int& bigger(int& p, int& q) { return p > q ? p : q; }
void show(int x, int y = 5, int z = 10) { cout << x + y + z << ' '; }

int main() {
    long long fee1 = 45000, fee2 = 45000, fee3 = 45000;
    applyByValue(fee1, 10);
    cout << "After call by value   : " << fee1 << '\n';
    applyByReference(fee2, 10);
    cout << "After call by reference: " << fee2 << '\n';
    applyByPointer(&fee3, 15);
    cout << "After call by pointer : " << fee3 << '\n';
    cout << "Returned fee (25%): " << applyAndReturn(45000, 25) << '\n';

    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    cout << a << ' ' << b << ' ' << c << '\n';
    bigger(a, c) = 100;
    cout << a << ' ' << c << '\n';
    show(1); show(1, 2); show(1, 2, 3); cout << '\n';
}
