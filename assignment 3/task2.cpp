#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

class Prescription {
    int n;
    std::string* medicines;
public:
    explicit Prescription(int count) : n(count), medicines(count > 0 ? new std::string[count] : nullptr) {
        if (count < 0) throw std::invalid_argument("negative medicine count");
    }
    Prescription(const Prescription& other)
        : n(other.n), medicines(n > 0 ? new std::string[n] : nullptr) {
        if (n > 0) std::copy(other.medicines, other.medicines + n, medicines);
        std::cout << "Deep copy constructor called\n";
    }
    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            std::string* fresh = other.n > 0 ? new std::string[other.n] : nullptr;
            if (other.n > 0) std::copy(other.medicines, other.medicines + other.n, fresh);
            delete[] medicines;
            medicines = fresh; n = other.n;
        }
        return *this;
    }
    ~Prescription() { delete[] medicines; }
    void set(int i, const std::string& m) { if(i<0||i>=n) throw std::out_of_range("index"); medicines[i]=m; }
    std::string get(int i) const { if(i<0||i>=n) throw std::out_of_range("index"); return medicines[i]; }
};
int main() {
    Prescription p(2); p.set(0,"Paracetamol"); p.set(1,"ORS");
    Prescription q=p; q.set(1,"Cetirizine");
    Prescription r(1); r=p; p.set(0,"Ibuprofen"); r=r;
    std::cout << p.get(0) << ' ' << p.get(1) << " | " << q.get(0) << ' ' << q.get(1)
              << " | " << r.get(0) << ' ' << r.get(1) << '\n';
}
