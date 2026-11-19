#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Original design: when full, shift all saved transactions left.
class ShiftingHistory {
    double data[10]{};
    int count = 0;
public:
    void add(double value) {
        if (count < 10) data[count++] = value;
        else {
            for (int i = 1; i < 10; ++i) data[i - 1] = data[i];
            data[9] = value;
        }
    }
    void print() const {
        for (int i = 0; i < count; ++i) cout << data[i] << ' ';
        cout << '\n';
    }
};

// Redesigned version: circular index overwrites the oldest item in O(1).
class CircularHistory {
    double data[10]{};
    int count = 0;
    int next = 0;
public:
    void add(double value) {
        data[next] = value;
        next = (next + 1) % 10;
        if (count < 10) ++count;
    }
    void printOldestToNewest() const {
        int start = (count == 10) ? next : 0;
        for (int i = 0; i < count; ++i) cout << data[(start + i) % 10] << ' ';
        cout << '\n';
    }
};

int main() {
    ShiftingHistory original;
    CircularHistory redesigned;
    for (int transaction = 1; transaction <= 12; ++transaction) {
        original.add(transaction * 100.0);
        redesigned.add(transaction * 100.0);
    }
    cout << "Original (last 10): ";
    original.print();
    cout << "Redesigned (last 10): ";
    redesigned.printOldestToNewest();
    cout << "Both designs retain transactions 300 through 1200.\n";
}
