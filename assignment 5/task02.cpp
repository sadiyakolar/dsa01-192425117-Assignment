#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <new>

class BillingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
class ClaimError : public BillingError {
public:
    using BillingError::BillingError;
};
class PackageError : public BillingError {
public:
    using BillingError::BillingError;
};
class PatientRecordError : public BillingError {
public:
    using BillingError::BillingError;
};

class Resource {
    std::string name;
public:
    explicit Resource(std::string n) : name(std::move(n)) {
        std::cout << "acquired " << name << '\n';
    }
    ~Resource() noexcept { std::cout << "released " << name << '\n'; }
};

double approve(double billed, double cover) {
    if (billed < 0 || cover < 0)
        throw std::invalid_argument("negative amount");
    if (billed > cover)
        throw ClaimError("exceeds cover");
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& e) {
        std::cout << "audit: " << e.what() << '\n';
        throw; // rethrows the same exception object and preserves its type
    }
}

double parseAmount(const std::string& value) {
    return std::stod(value);
}

void runTests() {
    Resource resource("claim-file");
    const std::vector<std::pair<double, double>> cases = {
        {40000, 50000}, {60000, 50000}, {-1, 50000}
    };
    for (const auto& c : cases) {
        try {
            std::cout << "approved " << settle(c.first, c.second) << '\n';
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << '\n';
        }
    }
}

int main() {
    runTests();

    try {
        std::cout << "parsed amount: " << parseAmount("not-a-number") << '\n';
    } catch (const std::invalid_argument& e) {
        std::cout << "input error: " << e.what() << '\n';
    }

    try {
        volatile std::size_t requested = static_cast<std::size_t>(-1) / 2;
        const std::size_t impossible = requested;
        std::unique_ptr<int[]> data(new int[impossible]);
        (void)data;
    } catch (const std::bad_alloc&) {
        std::cout << "memory allocation failed safely\n";
    } catch (const std::exception& e) {
        std::cout << "allocation error: " << e.what() << '\n';
    } catch (...) {
        std::cout << "unknown top-level error\n";
    }
}
