#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

class Bill {
protected:
    std::string patient;
public:
    explicit Bill(std::string p) : patient(std::move(p)) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(std::string p, double c, double t)
        : Bill(std::move(p)), consultation(c), tests(t) {
        if (c < 0 || t < 0) throw std::invalid_argument("negative charge");
    }
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};

class InPatientBill : public Bill {
    int days;
    double dailyRate, procedure;
public:
    InPatientBill(std::string p, int d, double rate, double proc)
        : Bill(std::move(p)), days(d), dailyRate(rate), procedure(proc) {
        if (d < 0 || rate < 0 || proc < 0) throw std::invalid_argument("invalid IP bill");
    }
    double total() const override { return days * dailyRate + procedure; }
    std::string type() const override { return "IP"; }
};

// New bill type added without modifying the existing bill classes.
class EmergencyBill : public Bill {
    double base, hourly;
    int hours;
public:
    EmergencyBill(std::string p, double b, double h, int hrs)
        : Bill(std::move(p)), base(b), hourly(h), hours(hrs) {
        if (b < 0 || h < 0 || hrs < 0) throw std::invalid_argument("invalid emergency bill");
    }
    double total() const override { return base + hourly * hours; }
    std::string type() const override { return "Emergency"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill&) const = 0;
    virtual std::string name() const = 0;
};
class Insurance : public Payer {
    double limit, copayPercent;
public:
    Insurance(double l, double c) : limit(l), copayPercent(c) {
        if (l < 0 || c < 0 || c > 100) throw std::invalid_argument("invalid policy");
    }
    double amountCovered(const Bill& b) const override {
        return std::min(limit, b.total() * (1.0 - copayPercent / 100.0));
    }
    std::string name() const override { return "Insurance"; }
};

// New payer added without changing existing payer classes.
class CorporatePayer : public Payer {
    double percent;
public:
    explicit CorporatePayer(double p) : percent(p) {
        if (p < 0 || p > 100) throw std::invalid_argument("invalid corporate percentage");
    }
    double amountCovered(const Bill& b) const override { return b.total() * percent / 100.0; }
    std::string name() const override { return "Corporate"; }
};

int main() {
    try {
        std::vector<std::unique_ptr<Bill>> bills;
        bills.push_back(std::make_unique<OutPatientBill>("Ravi", 500, 1200));
        bills.push_back(std::make_unique<InPatientBill>("Meena", 3, 2500, 40000));
        bills.push_back(std::make_unique<EmergencyBill>("Latha", 5000, 1500, 4));

        std::vector<std::unique_ptr<Payer>> payers;
        payers.push_back(std::make_unique<Insurance>(60000, 20));
        payers.push_back(std::make_unique<CorporatePayer>(75));

        for (const auto& bill : bills) {
            std::cout << bill->type() << " total = " << bill->total() << '\n';
            for (const auto& payer : payers)
                std::cout << "  " << payer->name() << " covers "
                          << payer->amountCovered(*bill) << '\n';
        }
        std::cout << "Extension test completed.\n";
    } catch (const std::exception& e) {
        std::cerr << "Billing error: " << e.what() << '\n';
        return 1;
    }
}
