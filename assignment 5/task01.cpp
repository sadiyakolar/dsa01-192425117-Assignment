#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>

class Bill {
protected:
    std::string patient;
public:
    explicit Bill(const std::string& p) : patient(p) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    const std::string& getPatient() const { return patient; }
    void print() const {
        std::cout << type() << " " << patient << ": " << std::fixed
                  << std::setprecision(2) << total() << '\n';
    }
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(const std::string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) {
        if (c < 0 || t < 0) throw std::invalid_argument("negative charge");
    }
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};

class InPatientBill : public Bill {
    int days;
    double perDay, procedures, medicines;
public:
    InPatientBill(const std::string& p, int d, double rate, double proc, double med)
        : Bill(p), days(d), perDay(rate), procedures(proc), medicines(med) {
        if (d < 0 || rate < 0 || proc < 0 || med < 0)
            throw std::invalid_argument("negative charge or days");
    }
    double total() const override { return days * perDay + procedures + medicines; }
    std::string type() const override { return "IP"; }
};

class DayCareBill : public Bill {
    double packagePrice;
public:
    DayCareBill(const std::string& p, double price) : Bill(p), packagePrice(price) {
        if (price < 0) throw std::invalid_argument("negative package price");
    }
    double total() const override { return packagePrice; }
    std::string type() const override { return "DayCare"; }
};

class EmergencyBill : public Bill {
    double baseCharge, hourlyCharge;
    int hours;
public:
    EmergencyBill(const std::string& p, double base, double hourly, int h)
        : Bill(p), baseCharge(base), hourlyCharge(hourly), hours(h) {
        if (base < 0 || hourly < 0 || h < 0)
            throw std::invalid_argument("negative emergency charge or hours");
    }
    double total() const override { return baseCharge + hourlyCharge * hours; }
    std::string type() const override { return "Emergency"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual std::string name() const = 0;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill&) const override { return 0.0; }
    std::string name() const override { return "SelfPay"; }
};

class Insurance : public Payer {
    double coverLimit, coPaymentPercent;
public:
    Insurance(double limit, double copay)
        : coverLimit(limit), coPaymentPercent(copay) {
        if (limit < 0 || copay < 0 || copay > 100)
            throw std::invalid_argument("invalid insurance settings");
    }
    double amountCovered(const Bill& bill) const override {
        return std::min(coverLimit, bill.total() * (1.0 - coPaymentPercent / 100.0));
    }
    std::string name() const override { return "Insurance"; }
};

class GovernmentScheme : public Payer {
    double packageRate;
public:
    explicit GovernmentScheme(double rate) : packageRate(rate) {
        if (rate < 0) throw std::invalid_argument("negative scheme rate");
    }
    double amountCovered(const Bill& bill) const override {
        return std::min(packageRate, bill.total());
    }
    std::string name() const override { return "GovernmentScheme"; }
};

class CorporatePayer : public Payer {
    double percentage;
public:
    explicit CorporatePayer(double percent) : percentage(percent) {
        if (percent < 0 || percent > 100) throw std::invalid_argument("invalid percentage");
    }
    double amountCovered(const Bill& bill) const override {
        return bill.total() * percentage / 100.0;
    }
    std::string name() const override { return "CorporatePayer"; }
};

int main() {
    try {
        std::vector<std::unique_ptr<Bill>> bills;
        bills.push_back(std::make_unique<OutPatientBill>("Ravi", 500, 1200));
        bills.push_back(std::make_unique<InPatientBill>("Meena", 3, 2500, 40000, 3000));
        bills.push_back(std::make_unique<DayCareBill>("Arun", 25000));
        bills.push_back(std::make_unique<EmergencyBill>("Latha", 5000, 1500, 4));

        std::vector<std::unique_ptr<Payer>> payers;
        payers.push_back(std::make_unique<SelfPay>());
        payers.push_back(std::make_unique<Insurance>(60000, 20));
        payers.push_back(std::make_unique<GovernmentScheme>(30000));
        payers.push_back(std::make_unique<CorporatePayer>(75));

        double dayTotal = 0;
        for (const auto& bill : bills) {
            bill->print();
            dayTotal += bill->total();
        }
        std::cout << "Day total: " << dayTotal << "\n\n";

        for (const auto& bill : bills) {
            std::cout << bill->type() << " / " << bill->getPatient() << '\n';
            for (const auto& payer : payers)
                std::cout << "  " << payer->name() << " covers "
                          << payer->amountCovered(*bill) << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Billing error: " << e.what() << '\n';
        return 1;
    }
}
