#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

inline int minutesBetween(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;
    return abs(first - second);
}

inline bool earlier(const Time& a, const Time& b) {
    return a.h * 60 + a.m < b.h * 60 + b.m;
}

// Separate benchmark pair for the assignment's inline investigation.
inline int fastMinuteValue(int h, int m) { return h * 60 + m; }
#if defined(__GNUC__)
__attribute__((noinline))
#endif
int regularMinuteValue(int h, int m) { return h * 60 + m; }

int main() {
    Time departure(9, 45), arrival(13, 10);
    cout << minutesBetween(departure, arrival) << ' '
         << boolalpha << earlier(arrival, departure) << '\n';
    Time beforeNoon(11, 50), afterNoon(12, 10);
    cout << minutesBetween(beforeNoon, afterNoon) << ' '
         << earlier(beforeNoon, afterNoon) << '\n';
    cout << minutesBetween(departure, departure) << ' '
         << earlier(departure, departure) << '\n';

    constexpr int iterations = 10000000;
    volatile long long result = 0;
    auto startInline = chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) result += fastMinuteValue(i % 24, i % 60);
    auto endInline = chrono::steady_clock::now();
    auto startRegular = chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) result += regularMinuteValue(i % 24, i % 60);
    auto endRegular = chrono::steady_clock::now();
    auto inlineUs = chrono::duration_cast<chrono::microseconds>(endInline - startInline).count();
    auto regularUs = chrono::duration_cast<chrono::microseconds>(endRegular - startRegular).count();
    cout << "Inline benchmark (microseconds): " << inlineUs << '\n';
    cout << "Regular benchmark (microseconds): " << regularUs << '\n';
    cout << "Benchmark checksum: " << result << '\n';
}
