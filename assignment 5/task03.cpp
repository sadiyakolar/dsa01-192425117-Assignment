#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <variant>
#include <cstdint>
#include <memory>

struct OutPatient {
    double consultation, tests;
    double total() const { return consultation + tests; }
};
struct InPatient {
    int days;
    double perDay, procedure, medicines;
    double total() const { return days * perDay + procedure + medicines; }
};

class Bill {
public:
    virtual ~Bill() = default;
    virtual double total() const = 0;
};
class OPBill final : public Bill {
    OutPatient data;
public:
    explicit OPBill(OutPatient d) : data(d) {}
    double total() const override { return data.total(); }
};
class IPBill final : public Bill {
    InPatient data;
public:
    explicit IPBill(InPatient d) : data(d) {}
    double total() const override { return data.total(); }
};

struct SwitchBill {
    enum class Kind { OP, IP } kind;
    double a, b, c, d;
};
double switchTotal(const SwitchBill& bill) {
    switch (bill.kind) {
        case SwitchBill::Kind::OP: return bill.a + bill.b;
        case SwitchBill::Kind::IP: return bill.a * bill.b + bill.c + bill.d;
    }
    return 0.0;
}
double variantTotal(const std::variant<OutPatient, InPatient>& bill) {
    return std::visit([](const auto& item) { return item.total(); }, bill);
}

template<class F>
double measureMilliseconds(F fn) {
    const auto start = std::chrono::steady_clock::now();
    volatile double sink = fn();
    (void)sink;
    const auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(stop - start).count();
}

int main() {
    const std::size_t smallN = 10;
    std::vector<SwitchBill> smallSwitch;
    std::vector<std::unique_ptr<Bill>> smallVirtual;
    for (std::size_t i = 0; i < smallN; ++i) {
        if (i % 2 == 0) {
            smallSwitch.push_back({SwitchBill::Kind::OP, 500.0, 1200.0, 0, 0});
            smallVirtual.push_back(std::make_unique<OPBill>(OutPatient{500, 1200}));
        } else {
            smallSwitch.push_back({SwitchBill::Kind::IP, 3, 2500, 40000, 3000});
            smallVirtual.push_back(std::make_unique<IPBill>(InPatient{3, 2500, 40000, 3000}));
        }
    }
    double switchSum = 0, virtualSum = 0;
    for (const auto& b : smallSwitch) switchSum += switchTotal(b);
    for (const auto& b : smallVirtual) virtualSum += b->total();
    std::cout << "10-bill switch total: " << switchSum << '\n';
    std::cout << "10-bill virtual total: " << virtualSum << '\n';

    std::cout << "\nTiming comparison (compile with -O2)\n";
    for (std::size_t n : {1000ULL, 1000000ULL, 10000000ULL}) {
        std::vector<SwitchBill> sw;
        sw.reserve(n);
        for (std::size_t i = 0; i < n; ++i) {
            if (i % 2 == 0) sw.push_back({SwitchBill::Kind::OP, 500, 1200, 0, 0});
            else sw.push_back({SwitchBill::Kind::IP, 3, 2500, 40000, 3000});
        }
        const double ms = measureMilliseconds([&] {
            double sum = 0;
            for (const auto& b : sw) sum += switchTotal(b);
            return sum;
        });
        std::cout << n << " bills, switch: " << ms << " ms\n";
    }

    // A compact variant demonstration. It avoids per-object heap allocation.
    std::vector<std::variant<OutPatient, InPatient>> variants;
    variants.reserve(1000000);
    for (std::size_t i = 0; i < 1000000; ++i) {
        if (i % 2 == 0) variants.emplace_back(OutPatient{500, 1200});
        else variants.emplace_back(InPatient{3, 2500, 40000, 3000});
    }
    const double variantMs = measureMilliseconds([&] {
        double sum = 0;
        for (const auto& b : variants) sum += variantTotal(b);
        return sum;
    });
    std::cout << "1000000 bills, variant/visit: " << variantMs << " ms\n";

    std::cout << "\nException versus return-code experiment (1,000,000 claims)\n";
    for (int invalidPercent : {0, 1, 50}) {
        const std::size_t n = 1000000;
        const std::size_t invalidCount = n * static_cast<std::size_t>(invalidPercent) / 100;
        std::vector<double> amounts(n, 400.0);
        for (std::size_t i = 0; i < invalidCount; ++i) amounts[i] = -1.0;

        const double returnMs = measureMilliseconds([&] {
            std::size_t errors = 0;
            for (double x : amounts) {
                if (x < 0) ++errors;
            }
            return static_cast<double>(errors);
        });
        const double exceptionMs = measureMilliseconds([&] {
            std::size_t errors = 0;
            for (double x : amounts) {
                try {
                    if (x < 0) throw std::invalid_argument("negative");
                } catch (const std::invalid_argument&) {
                    ++errors;
                }
            }
            return static_cast<double>(errors);
        });
        std::cout << invalidPercent << "% invalid: return-code " << returnMs
                  << " ms, exceptions " << exceptionMs << " ms\n";
    }
    std::cout << "Timings depend on CPU, compiler and system load; record your own run.\n";
}
